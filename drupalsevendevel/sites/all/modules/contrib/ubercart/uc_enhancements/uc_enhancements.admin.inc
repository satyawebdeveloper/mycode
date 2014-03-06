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
function uc_enhancements_settings_form($form, &$form_state) {
    $form['uc_enhancements_threshold_notification'] = array(
        '#type' => 'checkbox',
        '#title' => t('Send email notification when stock level reaches its threshold value'),
        '#default_value' => variable_get('uc_enhancements_threshold_notification', FALSE),
    );

    $form['uc_enhancements_threshold_notification_recipients'] = array(
        '#type' => 'textfield',
        '#title' => t('Notification recipients'),
        '#default_value' => variable_get('uc_enhancements_threshold_notification_recipients', uc_store_email()),
        '#description' => t('The list of comma-separated email addresses that will receive the notification.'),
    );

    $form['uc_enhancements_threshold_notification_subject'] = array(
        '#type' => 'textfield',
        '#title' => t('Message subject'),
        '#default_value' => variable_get('uc_enhancements_threshold_notification_subject', uc_get_message('uc_enhancements_threshold_notification_subject')),
    );

    $form['uc_enhancements_threshold_notification_message'] = array(
        '#type' => 'textarea',
        '#title' => t('Message text'),
        '#default_value' => variable_get('uc_enhancements_threshold_notification_message', uc_get_message('uc_enhancements_threshold_notification_message')),
        '#description' => t('The message the user receives when the stock level reaches its threshold value.'),
        '#rows' => 10,
    );

    if (module_exists('token')) {
        $form['token_tree'] = array(
            '#markup' => theme('token_tree', array('token_types' => array('uc_order', 'uc_enhancements', 'node', 'site', 'store'))),
        );
    }

    return system_settings_form($form);
}

/**
 * Form builder for product stock edit form.
 *
 * @see uc_enhancements_edit_form_submit()
 * @see theme_uc_enhancements_edit_form()
 * @ingroup forms
 */
function uc_enhancements_edit_form($form, &$form_state, $node) {
    drupal_set_title($node->title);
    drupal_add_css(drupal_get_path('module', 'uc_enhancements') . '/uc_enhancements.css');
    $selectedproductEnhancments = getProductEnchancements($node->nid);

    $result = loadCatalogProducts();
    $form = array();

    $form['productenhancements'] = array(
        '#type' => 'fieldset',
        '#prefix' => '<ul>',
        '#suffix' => '</ul>',
        '#weight' => 1,
    );

//  $form['productenhancements']['ALL'] = array(
//  '#type' =>'checkbox',
//   '#prefix' => '<li>',
//  '#suffix' => '</li>',
//      '#weight' =>2, 
//      '#title'=>t('ALL'),
//  
//  
//);


    foreach ($result as $productvalue) {

        foreach ($productvalue as $key => $productdetails) {

            $form['productenhancements'][$key] = array(
                '#type' => 'fieldset',
                '#prefix' => '<ul>',
                '#suffix' => '</ul>',
                '#weight' => 3,
            );
//            $form['productenhancements'][$key]['packages-' . $key] = array(
//                '#type' => 'checkbox',
//                '#prefix' => '<li>',
//                '#suffix' => '</li>',
//                '#weight' => 4,
//                '#return_value' => $key,
//                '#title' => t($key),
//            );
              
            $form['productenhancements'][$key]['packages-'.$key] = array(
  '#type' =>'item',
   '#prefix' => '<li>',
  '#suffix' => '</li>',
         '#weight' => 4,
          '#return_value' =>$key,
    

  '#title' => t($key),
);

            $form['productenhancements'][$key]['subs'] = array(
                '#type' => 'fieldset',
                '#prefix' => '<ul>',
                '#suffix' => '</ul>',
                '#weight' => 5,
            );
            $w = 5;
            foreach ($productdetails as $productform) {


                $producttitle = $string = preg_replace('/\s+/', '', $productform['title']);
                if (in_array($productform['nid'], $selectedproductEnhancments)) {
                    $form['productenhancements'][$key]['subs'][$producttitle] = array(
                        '#type' => 'checkbox',
                        '#prefix' => '<li>',
                        '#suffix' => '</li>',
                        '#weight' => $w + 1,
                        '#title' => t($productform['title']),
                        '#return_value' => $productform['nid'],
                        '#default_value' => 0,
                        '#attributes' => array('checked' => 'checked'),
                    );
                } else {
                    $form['productenhancements'][$key]['subs'][$producttitle] = array(
                        '#type' => 'checkbox',
                        '#prefix' => '<li>',
                        '#suffix' => '</li>',
                        '#weight' => $w + 1,
                        '#title' => t($productform['title']),
                        '#return_value' => $productform['nid'],
                        '#default_value' => 0,
                        '#states' => array(
                            'checked' => array(
                                ':input[name="packages-' . $key . '"]' => array('checked' => TRUE),
                            ),
                        ),
                    );
                }
            }
        }
    }
    $form['selectednodeid'] = array(
        '#type' => 'hidden',
        '#value' => $node->nid,
    );
    $form['actions'] = array('#type' => 'actions');
    $form['actions']['save'] = array(
        '#type' => 'submit',
        '#value' => t('Save changes'),
    );

    return $form;
}

/**
 * Form submission handler for uc_enhancements_edit_form().
 *
 * @see uc_enhancements_edit_form()
 * @see theme_uc_enhancements_edit_form()
 */
function uc_enhancements_edit_form_submit($form, &$form_state) {
//  var_dump($form_state['values']);

    $notrequiredarray = array(
        'packages', 'ALL', 'save',
        'form_build_id', 'form_token',
        'form_id',
        'op'
    );

    $enhancednodes = array();
    $productids = array();
    foreach ($form_state['values'] as $valkey => $value) {
        $arr = explode('-', $valkey);
        if (!in_array($arr[0], $notrequiredarray)) {
            $selectedproductnode = (int) $value;
            if ($selectedproductnode > 0)
                $productids[] = $selectedproductnode;
        }
    }
    $enhancednodes['enhancedproducts'] = $productids;
    // var_dump($enhancednodes);

    /**
     * Getting the Entire Product Enhancement selected Options
     * id,auto incrmented
     * nid,selected product nid
     * productenhancements
     * {enhancedproducts:array(productnodeid,productnodeid,productnodeid);
     * 
     * 
     * 
     */
    $newob = new stdClass();
    $newob->nid = $form_state['values']['selectednodeid'];
    $newob->productenhancements = (object) $enhancednodes;

    $result = db_select('uc_product_enhancements', 'c')
            ->fields('c')
            ->condition('nid', $form_state['values']['selectednodeid'], '=')
            ->execute();
    $num_of_results = $result->rowCount();
    $update = (int) $result->fetchField(0);

    if ($num_of_results >= 1) {
        drupal_write_record('uc_product_enhancements', $newob, $update);
    } else {
        drupal_write_record('uc_product_enhancements', $newob);
    }
    drupal_set_message(t('Product Enhancements settings saved.'));
}

/**
 * Returns HTML for uc_enhancements_edit_form().
 *
 * @param $variables
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @see uc_enhancements_edit_form()
 * @see uc_enhancements_edit_form_submit()
 * @ingroup themeable
 */
function theme_uc_enhancements_edit_form($variables) {
    $form = $variables['form'];
    drupal_add_js('misc/tableselect.js');

    $header = array(
        array('data' => '&nbsp;&nbsp;' . t('Product Enhancements'), 'class' => array('select-all')),
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
