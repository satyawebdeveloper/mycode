<?php

class GiftcardController extends DrupalDefaultEntityController {

    public function save($giftcard) {
        if (isset($giftcard->id) && ($giftcard->id != null)) {
            try {
                drupal_write_record('giftcard', $giftcard, array('id'));
                field_attach_update('giftcard', $giftcard);
            } catch (Exception $e) {
                watchdog("Giftcard", "Error while Updating the Gift Card");
            }
        } else {
            try {
                drupal_write_record('giftcard', $giftcard);
                field_attach_insert('giftcard', $giftcard);
            } catch (Exception $e) {
                watchdog("Giftcard", "Error while Inserting the Gift Card");
            }
        }
        module_invoke_all('entity_insert', $giftcard, 'giftcard');
        return $giftcard;
    }

    public function delete($id) {
        db_delete('giftcard')
                ->condition('id', $id, '=')
                ->execute();
    }

}