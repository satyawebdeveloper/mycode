<?php

/**
 * @file
 * Stock administration menu items.
 */

/**
 * Form builder for stock settings form.
 *
 * @ingroup forms
 */
function uc_entrees_settings_form($form, &$form_state) {
  $form['uc_entrees_threshold_notification'] = array(
      '#type' => 'checkbox',
      '#title' => t('Send email notification when stock level reaches its threshold value'),
      '#default_value' => variable_get('uc_entrees_threshold_notification', FALSE),
  );

  $form['uc_entrees_threshold_notification_recipients'] = array(
      '#type' => 'textfield',
      '#title' => t('Notification recipients'),
      '#default_value' => variable_get('uc_entrees_threshold_notification_recipients', uc_store_email()),
      '#description' => t('The list of comma-separated email addresses that will receive the notification.'),
  );

  $form['uc_entrees_threshold_notification_subject'] = array(
      '#type' => 'textfield',
      '#title' => t('Message subject'),
      '#default_value' => variable_get('uc_entrees_threshold_notification_subject', uc_get_message('uc_entrees_threshold_notification_subject')),
  );

  $form['uc_entrees_threshold_notification_message'] = array(
      '#type' => 'textarea',
      '#title' => t('Message text'),
      '#default_value' => variable_get('uc_entrees_threshold_notification_message', uc_get_message('uc_entrees_threshold_notification_message')),
      '#description' => t('The message the user receives when the stock level reaches its threshold value.'),
      '#rows' => 10,
  );

  if (module_exists('token')) {
    $form['token_tree'] = array(
        '#markup' => theme('token_tree', array('token_types' => array('uc_order', 'uc_entrees', 'node', 'site', 'store'))),
    );
  }

  return system_settings_form($form);
}

/**
 * Form builder for product stock edit form.
 *
 * @see uc_entrees_edit_form_submit()
 * @see theme_uc_entrees_edit_form()
 * @ingroup forms
 */
function uc_entrees_edit_form($form, &$form_state, $node) {
  drupal_set_title($node->title);
  drupal_add_css(drupal_get_path('module', 'uc_entrees') . '/uc_entrees.css');
  
  $entress = getEntreenodes();
  $result = loadCatalogProducts();
  $form = array();
  $form['entree'] = array(
      '#type' => 'fieldset',
      '#title' => t('Entree Configuration'),
      '#weight' => 1,
  );
  $productattributes = uc_attribute_load_product_attributes($node->nid);
  $selectedattribentrees=getProductAttributesbynodeid($node->nid);
  $collapsefirst = 0;
  foreach ($productattributes as $key => $atrrib) {
    if ($collapsefirst == 0) {
      $collapsed = FALSE;
    }
    else {
      $collapsed = TRUE;
    }

    $form['entree'][$atrrib->aid] = array(
        '#type' => 'fieldset',
        '#title' => t($atrrib->name),
        '#weight' => $atrrib->aid,
        '#collapsible' => TRUE,
        '#collapsed' => $collapsed,
        '#tree' => TRUE,
    );

    //Creating the Node Entree check boxes
    foreach ($entress as $nodeentrees) {
      $nid = key($nodeentrees);
      $entreetitle = $nodeentrees[$nid];
      $returnvalues=$nid.'-'.$atrrib->aid.'-'.$node->nid;
      
if(array_key_exists($atrrib->aid, $selectedattribentrees))
      {
      if(in_array($nid,$selectedattribentrees[$atrrib->aid]))
      {
      $form['entree'][$atrrib->aid][$nid] = array(
          '#type' => 'checkbox',
//      '#weight' =>2,
          '#return_value' => $returnvalues,
          '#title' => t($entreetitle),
           '#attributes'=>array('checked' => 'checked'),
      );
      }
      else {
       $form['entree'][$atrrib->aid][$nid] = array(
          '#type' => 'checkbox',
//      '#weight' =>2,
          '#return_value' => $returnvalues,
          '#title' => t($entreetitle),
      ); 
      }
      }
    else {
       $form['entree'][$atrrib->aid][$nid] = array(
          '#type' => 'checkbox',
//      '#weight' =>2,
          '#return_value' => $returnvalues,
          '#title' => t($entreetitle),
      ); 
      }
      
    }

    //End of Creating node Entree checkboxes


    $collapsefirst++;
  }


  $form['actions'] = array('#type' => 'actions');
  $form['actions']['save'] = array(
      '#type' => 'submit',
      '#value' => t('Save changes'),
  );

  return $form;
}

/**
 * Form submission handler for uc_entrees_edit_form().
 *
 * @see uc_entrees_edit_form()
 * @see theme_uc_entrees_edit_form()
 */
function uc_entrees_edit_form_submit($form, &$form_state) {
  /**
   * $attributeentrees=array('attrname'=>array(
   * attrid=>2,'entreenodes'=array(1,2))
   * );
   * 
   * 
   */
  $formentrees=array();
  $entreeresults=array();
  $notrequiredarray=array(
   'save',
   'form_build_id','form_token',
   'form_id',
   'op'
      
  );
  foreach ($form_state['values'] as $attirbname => $attr) {
   
          
    if(is_array($attr)&&!in_array($attirbname, $notrequiredarray))
    {
      //array of atrributes
      $entreenodes=array();
      foreach ($attr as $keys=>$entrees) {
        $attribidkey=$keys;
        if(is_string($entrees))
        {
          $productentrees=  explode('-', $entrees);
          //series array[0]=>entreenodeid,array[1]=>attrid,array[0]=>productnodeid
          if($attribidkey==$productentrees[0])
          {
         $entreenodeid=$productentrees[0];
         $attribid=$productentrees[1];
         $productid=$productentrees[2];
         $entreenodes[]=$entreenodeid;
         
          }
         
         
         
        }
        
        
        
         
      }
     
      if(count($entreenodes) > 0)
          {
      $entreeresults['attribid']=$attribid;
      $entreeresults['productid']=$productid;
      $entreeresults['entreenodes']=$entreenodes;
          }
      
    }
    
          if(isset($entreeresults))
    $formentrees[$attirbname]=$entreeresults;
    unset($entreeresults);
  }
 

  $entreeObj = new stdClass();
  $entreeObj->productnode =$productid;
  $entreeObj->atrrid =$productid;
  $entreeObj->created =REQUEST_TIME;
  $entreeObj->attributeentrees = (object) $formentrees;
  
  
  $result = db_select('uc_attribute_entrees', 'c')
            ->fields('c')
           ->condition('productnode',$productid, '=')
            ->execute();
    $num_of_results = $result->rowCount();
    $update=(int)$result->fetchField(0);
    
  if($num_of_results >= 1)
  {
//    drupal_json_output($entreeObj);exit();
   drupal_write_record('uc_attribute_entrees', $entreeObj, $update);
   drupal_set_message(t('Product Entree settings updated.'));
  }
  else {
       drupal_write_record('uc_attribute_entrees', $entreeObj);
       drupal_set_message(t('Product Entree settings saved.'));
  }
   

  
  
  
  
}

/**
 * Returns HTML for uc_entrees_edit_form().
 *
 * @param $variables
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @see uc_entrees_edit_form()
 * @see uc_entrees_edit_form_submit()
 * @ingroup themeable
 */
function theme_uc_entrees_edit_form($variables) {
  $form = $variables['form'];
  drupal_add_js('misc/tableselect.js');

  $header = array(
      array('data' => '&nbsp;&nbsp;' . t('Product Attribute Entrees '), 'class' => array('select-all')),
  );
  $rows = array();

  foreach (element_children($form['stock']) as $id) {
    $rows[] = array(
        array('data' => drupal_render($form['stock'][$id]['active'])),
        array('data' => drupal_render($form['stock'][$id]['display_sku'])),
        array('data' => drupal_render($form['stock'][$id]['stock'])),
        array('data' => drupal_render($form['stock'][$id]['threshold'])),
    );
  }

  return theme('table', array('header' => $header, 'rows' => $rows)) . drupal_render_children($form);
}
