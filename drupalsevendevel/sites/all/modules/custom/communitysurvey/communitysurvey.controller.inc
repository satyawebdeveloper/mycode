<?php

/**
 * Controller for loading, creating, and saving communitysurvey.
 *
 * The default loader, which we extend, handles load() already. We only
 * need to add saving and creating.
 */
class CommunitySurveyController extends DrupalDefaultEntityController {

    public function save($communitysurvey) {
        $transaction = db_transaction();

        try {
            global $user;

            // Determine if we will be inserting a new communitysurvey.
            $communitysurvey->is_new = empty($communitysurvey->id);

            // Set the timestamp fields.
            if (empty($communitysurvey->created)) {
                $communitysurvey->created = REQUEST_TIME;
            }
            $communitysurvey->changed = REQUEST_TIME;

            $communitysurvey->revision_timestamp = REQUEST_TIME;
            $update_communitysurvey = TRUE;

            // Give modules the opportunity to prepare field data for saving.
            field_attach_presave('communitysurvey', $communitysurvey);

            // When saving a new communitysurvey revision, unset any existing $communitysurvey->vid
            // to ensure a new revision will actually be created and store the old
            // revision ID in a separate property for communitysurvey hook implementations.
//      if (!$communitysurvey->is_new && !empty($communitysurvey->revision) && $communitysurvey->vid) {
//        $communitysurvey->old_vid = $communitysurvey->vid;
//        unset($communitysurvey->vid);
//      }
            // If this is a new communitysurvey...
            if ($communitysurvey->is_new) {
                // Save the new communitysurvey.
                drupal_write_record('communitysurvey', $communitysurvey);

                // Save the initial revision.
//                $this->saveRevision($communitysurvey, $user->uid);

                $op = 'insert';
            } else {
                // Save the updated communitysurvey.
                drupal_write_record('communitysurvey', $communitysurvey, 'id');

                // If a new communitysurvey revision was requested, save a new record for that;
                // otherwise, update the communitysurvey revision record that matches the value
                // of $communitysurvey->vid.
                if (!empty($communitysurvey->revision)) {
                    $this->saveRevision($communitysurvey, $user->uid);
                } else {
                    $this->saveRevision($communitysurvey, $user->uid, TRUE);
                    $update_communitysurvey = FALSE;
                }

                $op = 'update';
            }

            // If the revision ID is new or updated, save it to the communitysurvey.
//      if ($update_communitysurvey) {
//        db_update('communitysurvey')
//          ->fields(array('vid' => $communitysurvey->vid))
//          ->condition('id', $communitysurvey->id)
//          ->execute();
//      }
            // Save fields.
            $function = 'field_attach_' . $op;
            $function('communitysurvey', $communitysurvey);

            module_invoke_all('entity_' . $op, $communitysurvey, 'communitysurvey');

            // Clear internal properties.
            unset($communitysurvey->is_new);

            // Ignore slave server temporarily to give time for the saved order to be
            // propagated to the slave.
            db_ignore_slave();

            return $communitysurvey;
        } catch (Exception $e) {
            $transaction->rollback();
            watchdog_exception('communitysurvey', $e, NULL, WATCHDOG_ERROR);
            return FALSE;
        }
    }

    /**
     * Saves an communitysurvey revision with the uid of the current user.
     *
     * @param $communitysurvey
     *   The fully loaded communitysurvey object.
     * @param $uid
     *   The user's uid for the current revision.
     * @param $update
     *   TRUE or FALSE indicating whether or not the existing revision should be
     *     updated instead of a new one created.
     */
    function saveRevision($communitysurvey, $uid, $update = FALSE) {
        // Hold on to the communitysurvey's original creator_uid but swap in the revision's
        // creator_uid for the momentary write.
        $temp_uid = $communitysurvey->uid;
        $communitysurvey->uid = $uid;

        // Update the existing revision if specified.
        if ($update) {
            drupal_write_record('communitysurvey_revision', $communitysurvey, 'vid');
        } else {
            // Otherwise insert a new revision. This will automatically update $communitysurvey
            // to include the vid.
            drupal_write_record('communitysurvey_revision', $communitysurvey);
        }

        // Reset the order's creator_uid to the original value.
        $communitysurvey->uid = $temp_uid;
    }

    /**
     * Deletes multiple communitysurvey by ID.
     *
     * @param $ids
     *   An array of communitysurvey IDs to delete.
     * @return
     *   TRUE on success, FALSE otherwise.
     */
    public function delete($ids) {
        if (!empty($ids)) {
            $communitysurvey = $this->load($ids, array());

            $transaction = db_transaction();

            try {
                db_delete('communitysurvey')
                        ->condition('id', $ids, 'IN')
                        ->execute();

                db_delete('communitysurvey_revision')
                        ->condition('id', $ids, 'IN')
                        ->execute();

                foreach ($communitysurvey as $communitysurvey_id => $communitysurvey) {
                    field_attach_delete('communitysurvey', $communitysurvey);
                }

                // Ignore slave server temporarily to give time for the
                // saved communitysurvey to be propagated to the slave.
                db_ignore_slave();
            } catch (Exception $e) {
                $transaction->rollback();
                watchdog_exception('communitysurvey', $e, NULL, WATCHDOG_ERROR);
                return FALSE;
            }

            module_invoke_all('entity_delete', $communitysurvey, 'communitysurvey');

            // Clear the page and block and communitysurvey caches.
            cache_clear_all();
            $this->resetCache();
        }

        return TRUE;
    }

    /**
     * Create a default communitysurvey.
     *
     * @param $type
     *   The machine-readable type of the communitysurvey.
     *
     * @return
     *   An communitysurvey object with all default fields initialized.
     */
    public function create($type = '') {
        return (object) array(
                    'uid' => '',
                    'type' => $type,
                    'areu_survey' => '',
                    'industry_survey' => '',
                    
        );
    }

}
