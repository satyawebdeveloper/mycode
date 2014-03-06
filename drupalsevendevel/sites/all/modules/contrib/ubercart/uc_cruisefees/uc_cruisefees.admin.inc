<?php

/**
 * @file
 * Attribute administration menu items.
 */

/**
 * Displays a paged list and overview of existing product attributes.
 */
function uc_cruisefees_admin($node) {
  $header = array(t('Name'),
      t('Amount'),
      t('Weight'),
      array('data' => t('Operations'), 'colspan' => 2));
$ucfees=uc_cruise_fees_load($node->nid);
//var_dump($ucfees);
  $rows = array();
  foreach ($ucfees as $key => $chargelineitem) {
    $rows[] = array(
      check_plain($chargelineitem->name),
     $chargelineitem->amount,
      $chargelineitem->weight,
       
      l(t('edit'), 'node/'.$node->nid.'/edit/cruisefees/'.$chargelineitem->id.'/edit'),
     l(t('delete'), 'node/'.$node->nid.'/edit/cruisefees/'.$chargelineitem->id.'/delete'),
    );
  }

  $build['cruisefees'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('No Fees available.'),
  );
  $build['pager'] = array(
    '#theme' => 'pager',
  );

  return $build;
}

/**
 * Form builder for product attributes.
 *
 * @see uc_cruisefees_form_submit()
 * @ingroup forms
 */
function uc_cruisefees_form($form, &$form_state, $object,$cruisefee = NULL) {
  
  $ucfees=uc_cruise_fees_load($object->nid,$cruisefee);
  
 if(isset($cruisefee))
    {
     $form['id'] = array(
  '#type' => 'hidden', 
   '#value' =>$cruisefee, 
);
  }
    
     $form['cruiseeventid'] = array(
  '#type' => 'hidden', 
   '#value' =>$object->nid, 
);
    
    
  $form['name'] = array(
  '#type' => 'textfield', 
  '#title' => t('Name'), 
  '#default_value' =>$cruisefee ? $ucfees->name:'', 
  '#size' =>20, 
  '#maxlength' => 128, 
  '#required' => TRUE,

);
 $form['amount'] = array(
  '#type' => 'textfield', 
  '#title' => t('Amount'), 
  '#default_value' =>$cruisefee ? $ucfees->amount:'', 
  '#size' =>20, 
  '#maxlength' => 128, 
  '#required' => TRUE,

);
 
 $form['itemweight'] = array(
       '#type' => 'select',
       '#title' => t('Line Item Weight'),
       '#options' => array(
          0 =>0,1 =>1, 2=>2,3=>3,
       ),
       '#default_value' =>$cruisefee ? $ucfees->weight:0, 
       '#description' => t('Set the Line Item weight which are used for sorting purpose'),
   );
 
 
 
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#suffix' => l(t('Cancel'), 'node/'.$object->nid.'/edit/cruisefees'),
  );

  return $form;
  
}

function uc_cruisefees_delete_form($form, &$form_state, $object,$cruisefee = NULL)
{
  if (!$ucfees=uc_cruise_fees_load($object->nid,$cruisefee)) {
    drupal_set_message(t('That cruise rate does not exist.'), 'error');
    drupal_goto('node/'.$object->nid.'/edit/cruisefees');
  }

  $form['fid'] = array(
    '#type' => 'value',
    '#value' => $cruisefee,
  );
  
  $form['nid'] = array(
    '#type' => 'hidden',
    '#value' => $object->nid,
  );
  $form['name'] = array(
    '#type' => 'value',
    '#value' => $ucfees->name,
  );

  return confirm_form($form, t('Are you sure you want to delete @name?',
          array('@name' => $ucfees->name)), 'node/'.$object->nid.'/edit/cruisefees',
          t('This action cannot be undone. '), t('Delete'), t('Cancel'));
}



/**
 * Form submission handler for uc_taxes_delete_form().
 *
 * @see uc_taxes_delete_form()
 */
function uc_cruisefees_delete_form_submit($form, &$form_state, $object,$cruisefee = NULL) {
  // Delete the tax rate.
  uccruisefees_delete($form_state['values']['fid']);

  // Display a message and redirect back to the overview.
  drupal_set_message(t('Fee rate %name deleted.', array('%name' => $form_state['values']['name'])));

  $form_state['redirect'] = 'node/'.$form_state['values']['nid'].'/edit/cruisefees';
}
//end of lineitems deletion


/**
 * Deletes a tax rate from the database.
 *
 * @param $rate_id
 *   The ID of the tax rate to delete.
 */
function uccruisefees_delete($fid) {
  // Delete the tax rate record.
  db_delete('uc_cruiseevent_fees')
    ->condition('id', $fid)
    ->execute();
}


/**
 * Form submission handler for uc_cruisefees_form().
 *
 * @see uc_cruisefees_form()
 */
function uc_cruisefees_form_submit($form, &$form_state,$object,$cruisefee = NULL) {
  
  
  
  
  //Building the Object using the constructor
 $uccruisefees=new UcCruisefees();
 $uccruisefees->id=$form_state['values']['id'];
 $uccruisefees->cruiseeventid=$form_state['values']['cruiseeventid'];
 $uccruisefees->name=$form_state['values']['name'];
 $uccruisefees->amount=$form_state['values']['amount'];
 $uccruisefees->weight=$form_state['values']['itemweight'];
 
 
 
 $formsaveresult= uc_cruisefees_save($uccruisefees);
 if($formsaveresult)
 {
   drupal_set_message('Record Inserted Sucessfully');
   drupal_goto('node/'.$uccruisefees->cruiseeventid.'/edit/cruisefees');
}
           
           
 
}


function uc_cruisefees_save($uccruisefees)
{
   if (empty($uccruisefees->id)) {
    $saveobj=  drupal_write_record('uc_cruiseevent_fees', $uccruisefees);
  }
  // Otherwise update the existing tax rate's data.
  else {
    $saveobj=  drupal_write_record('uc_cruiseevent_fees', $uccruisefees, array('id'));
  }
  
  return $saveobj;
}
/**
 * Confirms the deletion of the given attribute.
 *
 * @see uc_cruisefees_delete_confirm_submit()
 */
function uc_cruisefees_delete_confirm($form, &$form_state, $attribute) {
  
}

/**
 * Form submission handler for uc_cruisefees_delete_confirm().
 *
 * @see uc_cruisefees_delete_confirm()
 */
function uc_cruisefees_delete_confirm_submit($form, &$form_state) {
  
}


/**
 * Form to associate attributes with products or classes.
 *
 * @see uc_object_attributes_form_submit()
 * @see theme_uc_object_attributes_form()
 * @ingroup forms
 */
function uc_object_cruisefees_form($form, &$form_state, $object, $type, $view = 'overview') {
  echo 'great';
}

/**
 * Displays the formatted attribute form.
 *
 * @param $variables
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @see uc_object_attributes_form()
 * @ingroup themeable
 */
function theme_uc_object_cruisefees_form($variables) {
 
}

/**
 * Form submission handler for uc_object_attributes_form().
 *
 * @see uc_object_attributes_form()
 */
function uc_object_cruisefees_form_submit($form, &$form_state) {
  
}
