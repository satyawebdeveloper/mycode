<?php

class cruiseimagesController extends DrupalDefaultEntityController {

    public function save($cruiseimages) {
        if (isset($cruiseimages->id) && ($cruiseimages->id != null)) {
            try {
                drupal_write_record('cruiseimages', $cruiseimages, array('id'));
                field_attach_update('cruiseimages', $cruiseimages);
            } catch (Exception $e) {
                watchdog("cruiseimages", "Error while Updating the Gift Card");
            }
        } else {
            try {
                drupal_write_record('cruiseimages', $cruiseimages);
                field_attach_insert('cruiseimages', $cruiseimages);
            } catch (Exception $e) {
                watchdog("cruiseimages", "Error while Inserting the Gift Card");
            }
        }
        module_invoke_all('entity_insert', $cruiseimages, 'cruiseimages');
        return $cruiseimages;
    }

    public function delete($id) {
        db_delete('cruiseimages')
                ->condition('id', $id, '=')
                ->execute();
    }

}