<?php

function giftcard_add() {

    $giftcard = (object) array(
                'id' => '',
                'card_id' => '',
                'flag' => '',
                'created' => '',
    );

    return drupal_get_form('giftcard_add_form', $giftcard);
}

function giftcard_add_form($form, &$form_state, $giftcard) {

    $formstatus = $giftcard->id == '' ? "add" : "edit";
    $form['operation'] = array(
        '#type' => 'hidden',
        '#value' => $formstatus
    );

    $auto_id = $giftcard->id != '' ? $giftcard->id : "";
    $form['auto_id'] = array(
        '#type' => 'hidden',
        '#value' => $auto_id
    );


    $form['cardid'] = array(
        '#type' => 'textfield',
        '#title' => t('Card ID'),
        '#default_value' => isset($giftcard->card_id) ? $giftcard->card_id : '',
    );
    field_attach_form('giftcard', $giftcard, $form, $form_state);
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
    );
    return $form;
}

function giftcard_add_form_validate($form, &$form_state) {
    $giftcard = (object) $form_state['values'];
    field_attach_form_validate('giftcard', $giftcard, $form, $form_state);
}

function giftcard_add_form_submit($form, &$form_state) {


    $card_id = $form_state['values']['cardid'];
    $auto_id = $form_state['values']['auto_id'];

    $giftcard = new stdClass();
    $giftcard->id = $auto_id;
    $giftcard->card_id = $card_id;
    $giftcard->created = time();
    $giftcard->flag = "0";
    field_attach_submit('giftcard', $giftcard, $form, $form_state);
    $giftcard = giftcard_save($giftcard);

    $operation = $form_state['values']['operation'];
    $msg = '';
    if ($operation == "add") {
        $msg = 'Gift Card Created Successfully.';
    } else {
        $msg = 'Gift Card Updated Successfully.';
    }

    drupal_set_message($msg);
    $form_state['redirect'] = 'admin/structure/giftcard/manage';
}