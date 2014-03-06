<?php

function dropdownbtnactionpage() {
    //return "hello";
    return drupal_get_form("ticketentreedropdown");
}

function ticketentreedropdown($form, &$form_state) {
    $options_first = get_tickets();
    $selected = isset($form_state['values']['tickets']) ? $form_state['values']['tickets'] : key($options_first);

    $form['tickets'] = array(
        '#type' => 'select',
        '#title' => 'Ticket',
        '#options' => $options_first,
        '#default_value' => $selected,
        '#ajax' => array(
            'callback' => 'ajx_dropdowncallback',
            'wrapper' => 'dropdown-second-replace',
        ),
    );

    $form['entrees'] = array(
        '#type' => 'select',
        '#title' => $options_first[$selected] . ' ' . t('Entree'),
        '#prefix' => '<div id="dropdown-second-replace">',
        '#suffix' => '</div>',
        '#options' => get_entrees($selected),
        '#default_value' => isset($form_state['values']['entrees']) ? $form_state['values']['entrees'] : '',
    );
    return $form;
}

function get_entrees($key = '') {
    $options = array(
        t('General') => drupal_map_assoc(array(t('A'), t('B'), t('C'), t('D'))),
        t('Senior') => drupal_map_assoc(array(t('a'), t('b'), t('c'), t('d'))),
    );
    if (isset($options[$key])) {
        return $options[$key];
    } else {
        return array();
    }
}

function get_tickets() {
    return drupal_map_assoc(array(t('General'), t('Senior')));
}

function ajx_dropdowncallback($form, $form_state) {
    return $form['entrees'];
}