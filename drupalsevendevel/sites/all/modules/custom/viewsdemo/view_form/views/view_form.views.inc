<?php
/**
 * @file
 */

/**
 * Implements hook_views_data_alter().
 *
 * @param $data
 *   Information about Views' tables and fields.
 */
function view_form_views_data_alter(&$data) {
  // Add the Title form field to the node-related fields.
  $data['node']['title_edit'] = array(
    'field' => array(
      'title' => t('Title form field'),
      'help' => t('Edit the node title'),
      'handler' => 'view_form_field_handler_title_edit',
    ),
  );
}
