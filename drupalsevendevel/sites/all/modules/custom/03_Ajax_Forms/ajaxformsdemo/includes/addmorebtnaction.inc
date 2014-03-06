<?php

function addmorebtnactionpage() {
    return drupal_get_form("ajax_example_add_mores_form");
}

function ajax_example_add_mores_form($form, &$form_state) {
    $form['vouchers_fieldset'] = array(
        '#type' => 'markup',
        '#prefix' => '<div id="vocuhers-fieldset-wrapper">',
        '#suffix' => '</div>',
    );
    if (empty($form_state['num_vouchers'])) {
        $form_state['num_vouchers'] = 1;
    }
    for ($i = 1; $i <= $form_state['num_vouchers']; $i++) {

        $form['vouchers_fieldset']['vouchermessage' . $i] = array(
            '#type' => 'markup',
            '#prefix' => '<div id="vouchermessage' . $i . '">',
            '#suffix' => '</div>',
        );

        $form['vouchers_fieldset']['voucher' . $i] = array(
            '#type' => 'textfield',
            '#title' => t('Voucher#' . $i),
        );

        $form['vouchers_fieldset']['vocuher_applybutton' . $i] = array(
            '#type' => 'button',
            '#name' => $i,
            '#value' => t('Apply Vocuher'),
            '#prefix' => '',
            '#suffix' => '',
            '#limit_validation_errors' => array(),
            '#ajax' => array(
                'callback' => 'ajax_isvalidvoucher',
            ),
        );
    }


    $form['vouchers_fieldset']['vocuher_addbutton'] = array(
        '#type' => 'submit',
        '#value' => t('Add one more Vocucher'),
        '#submit' => array('ajax_add_textfield_action'),
        '#ajax' => array(
            'callback' => 'ajax_textfield_add_callback',
            'wrapper' => 'vocuhers-fieldset-wrapper',
        ),
    );


    if ($form_state['num_vouchers'] > 1) {
        $form['vouchers_fieldset']['vocuher_removebutton'] = array(
            '#type' => 'submit',
            '#value' => t('Remove Vocucher'),
            '#submit' => array('ajax_remove_textfield_action'),
            '#ajax' => array(
                'callback' => 'ajax_textfield_remove_callbacks',
                'wrapper' => 'vocuhers-fieldset-wrapper',
            ),
        );
    }



    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit'),
        '#submit' => array('ajax_example_add_mores_form_submit'),
    );

    $form['lname'] = array(
        '#type' => 'textfield',
        '#value' => t('LName'),
    );



    return $form;
}

function ajax_textfield_add_callback($form, $form_state) {
    return $form['vouchers_fieldset'];
}

function ajax_add_textfield_action($form, &$form_state) {
    $form_state['num_vouchers']++;
    $form_state['rebuild'] = TRUE;
}

//remove action
function ajax_textfield_remove_callbacks($form, $form_state) {
    return $form['vouchers_fieldset'];
}

function ajax_remove_textfield_action($form, &$form_state) {
    $form_state['num_vouchers']--;
    $form_state['rebuild'] = TRUE;
}

function ajax_example_add_mores_form_submit($form, &$form_state) {
    var_dump('test');
    exit();
}

function ajax_isvalidvoucher($form, $form_state) {
    $id = $form_state['triggering_element']['#name'];
    $commands[] = ajax_command_replace("#vouchermessage" . $id, "<div id='vouchermessage'.$id.'>" . $id . "</div>");

    return array('#type' => 'ajax', '#commands' => $commands);
}

