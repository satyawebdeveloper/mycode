<?php

/**
 * Menu callback; Show list of communitysurvey types we can add.
 */
function communitysurvey_add_page() {
    $item = menu_get_item();
    $links = system_admin_menu_block($item);

    foreach ($links as $link) {
        $items[] = l($link['title'], $link['href'], $item['localized_options'])
                . ': ' . filter_xss_admin($link['description']);
    }

    return theme('item_list', array('items' => $items));
}

/**
 * Present an communitysurvey submission form.
 */
function communitysurvey_add($type) {
    global $user;

    $types = communitysurvey_types();
    $type = isset($type) ? str_replace('-', '_', $type) : NULL;
    if (empty($types[$type])) {
        return MENU_NOT_FOUND;
    }

    $communitysurvey = entity_get_controller('communitysurvey')->create($type);

    drupal_set_title(t('Create @name', array('@name' => $types[$type]->name)), PASS_THROUGH);
    return drupal_get_form($type . '_communitysurvey_form', $communitysurvey);
}

/**
 * Menu callback; presents the communitysurvey editing form, or redirects to delete confirmation.
 *
 * @param $communitysurvey
 *   The communitysurvey object to edit.
 */
function communitysurvey_page_edit($communitysurvey) {
    $types = communitysurvey_types();
    drupal_set_title(t('<em>Edit @type</em> @title', array('@type' => $types[$communitysurvey->type]->name, '@title' => $communitysurvey->uid)), PASS_THROUGH);

    return drupal_get_form($communitysurvey->type . '_communitysurvey_form', $communitysurvey);
}

/**
 * Form builder; Displays the communitysurvey add/edit form.
 *
 * @param $form
 * @param $form_state
 * @param $communitysurvey
 *   The communitysurvey object to edit, which may be brand new.
 */
function communitysurvey_form($form, &$form_state, $communitysurvey) {

    // Set the id and identify this as an communitysurvey edit form.
    $form['#id'] = 'communitysurvey-form';

    // Save the communitysurvey for later, in case we need it.
    $form['#communitysurvey'] = $communitysurvey;
    $form_state['communitysurvey'] = $communitysurvey;

    // Common fields. We don't have many.

    $form['uid'] = array(
        '#type' => 'textfield',
        '#title' => t('User ID'),
        //'#default_value' => $communitysurvey->title,
        //'#weight' => -5,
        '#required' => TRUE,
    );

    //2 Ways we can store the data either key or value. 
    $options = array(
        'chkitnessclub' => t('Fitness Club'),
        'chk_atc' => t('Athletic/Team/Club'),
        'chk_icc' => t('Instructor/Coach/Community Leader'),
        'chk_com_mem' => t('Community Member'),
        'chk_business' => t('Business'),
        'chk_edugroup' => t('Education Group'),
        'chkfitnessclub' => t('Entertainment Business'),
        'chkareu_other' => t('Other'),
    );
    $form['areyoua'] = array(
        '#title' => t('Are You a(n)?'),
        '#type' => 'checkboxes',
        //'#description' => t('Please enter your name.'),
        //'#options' => $options,
        '#options' => drupal_map_assoc(array(t('Fitness Club'), t('Athletic/Team/Club'), t('Instructor/Coach/Community Leader'), t('Community Member'), t('Business'), t('Education Group'), t('Entertainment Business'), t('Other'))),
    );


    $options2 = array(
        'chkfitness' => t('Fitness'),
        'chk_athletic' => t('Athletic'),
        'chk_college' => t('College'),
        'chk_youth' => t('Youth'),
        'chk_businessclub' => t('Business'),
        'chk_entertainment' => t('Entertainment'),
        'chk_nonprofit' => t('Non Profit'),
        'chkadd_other' => t('Other'),
    );
    $form['industry'] = array(
        '#title' => t('Please Indicate Your Industry'),
        '#type' => 'checkboxes',
        //'#description' => t('Please enter your name.'),
        //'#options' => $options2,
        '#options' => drupal_map_assoc(array(t('Fitness'), t('Athletic'), t('College'), t('Youth'), t('Business'), t('Entertainment'), t('Non Profit'), t('Other'))),
    );






    // Add the buttons.
    $form['buttons'] = array();
    $form['buttons']['#weight'] = 100;
    $form['buttons']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
        '#weight' => 5,
        '#submit' => array('communitysurvey_form_submit'),
    );
    if (!empty($communitysurvey->id)) {
        $form['buttons']['delete'] = array(
            '#access' => user_access('delete communitysurvey'),
            '#type' => 'submit',
            '#value' => t('Delete'),
            '#weight' => 15,
            '#submit' => array('communitysurvey_form_delete_submit'),
        );
    }

    $form['#validate'][] = 'communitysurvey_form_validate';

    field_attach_form('communitysurvey', $communitysurvey, $form, $form_state);

    return $form;
}

function communitysurvey_form_validate($form, &$form_state) {
    $communitysurvey = $form_state['communitysurvey'];

    // Field validation.
    field_attach_form_validate('communitysurvey', $communitysurvey, $form, $form_state);
}

function communitysurvey_form_submit($form, &$form_state) {
    global $user;

    $communitysurvey = &$form_state['communitysurvey'];

    // Set the communitysurvey's uid if it's being created at this time.
//    if (empty($communitysurvey->uid)) {
//        $communitysurvey->uid = $user->uid;
//    }



    $areu = implode(',', $form_state['input']['areyoua']);
    $industry = implode(',', $form_state['input']['industry']);


    $communitysurvey->uid = $form_state['values']['uid'];
    $communitysurvey->areu_survey = $areu;
    $communitysurvey->industry_survey = $industry;



    // $communitysurvey->title = $form_state['values']['title'];
    //$communitysurvey->title = $form_state['values']['title'];
    //$communitysurvey->revision = $form_state['values']['revision'];
    // Notify field widgets.
    field_attach_submit('communitysurvey', $communitysurvey, $form, $form_state);
    communitysurvey_save($communitysurvey);
    // var_dump($communitysurvey);
    // exit();
    // Save the communitysurvey.
//    var_dump(communitysurvey_save($communitysurvey));
//    exit();
    // Notify the user.
    drupal_set_message(t('Record saved.'));

    // $form_state['redirect'] = 'communitysurvey/add' . $communitysurvey->id;
    $form_state['redirect'] = 'communitysurvey/add';
}

function communitysurvey_form_delete_submit($form, &$form_state) {
    $destination = array();
    if (isset($_GET['destination'])) {
        $destination = drupal_get_destination();
        unset($_GET['destination']);
    }
    $communitysurvey = $form['#communitysurvey'];
    $form_state['redirect'] = array('communitysurvey/' . $communitysurvey->id . '/delete', array('query' => $destination));
}

/**
 * Displays an communitysurvey.
 *
 * @param $communitysurvey
 *   The communitysurvey object to display.
 * @param $view_mode
 *   The view mode we want to display.
 */
function communitysurvey_page_view($communitysurvey, $view_mode = 'full') {
    // Remove previously built content, if exists.
    $communitysurvey->content = array();

    if ($view_mode == 'teaser') {
        $communitysurvey->content['title'] = array(
            '#markup' => filter_xss($communitysurvey->title),
            '#weight' => -5,
        );
    }

    // Build fields content.
    field_attach_prepare_view('communitysurvey', array($communitysurvey->id => $communitysurvey), $view_mode);
    entity_prepare_view('communitysurvey', array($communitysurvey->id => $communitysurvey));
    $communitysurvey->content += field_attach_view('communitysurvey', $communitysurvey, $view_mode);

    return $communitysurvey->content;
}

/**
 * Form bulder; Asks for confirmation of communitysurvey deletion.
 */
function communitysurvey_delete_confirm($form, &$form_state, $communitysurvey) {
    $form['#communitysurvey'] = $communitysurvey;
    // Always provide entity id in the same form key as in the entity edit form.
    $form['id'] = array('#type' => 'value', '#value' => $communitysurvey->id);
    return confirm_form($form, t('Are you sure you want to delete %title?', array('%title' => $communitysurvey->title)), 'communitysurvey/' . $communitysurvey->id, t('This action cannot be undone.'), t('Delete'), t('Cancel')
    );
}

/**
 * Executes communitysurvey deletion.
 */
function communitysurvey_delete_confirm_submit($form, &$form_state) {
    if ($form_state['values']['confirm']) {
        $communitysurvey = communitysurvey_load($form_state['values']['id']);
        communitysurvey_delete($form_state['values']['id']);
        watchdog('communitysurvey', '@type: deleted %title.', array('@type' => $communitysurvey->type, '%title' => $communitysurvey->title));

        $types = communitysurvey_types();
        drupal_set_message(t('@type %title has been deleted.', array('@type' => $types[$communitysurvey->type]->name, '%title' => $communitysurvey->title)));
    }

    $form_state['redirect'] = '<front>';
}

/**
 * Menu callback; Displays a listing of recent communitysurvey.
 *
 * This doesn't really work yet because our presentation code doesn't show
 * the title.
 */
function communitysurvey_page_list_recent() {
    $content = array();

    $query = new EntityFieldQuery();
    $query
            ->entityCondition('entity_type', 'communitysurvey')
            ->propertyOrderBy('created', 'DESC')
            ->fieldCondition('field_artist', 'value', 'Da Vinci', 'CONTAINS', 0)
            ->range(0, 5);
    $result = $query->execute();

    $communitysurvey = communitysurvey_load_multiple(array_keys($result['communitysurvey']));
    foreach ($communitysurvey as $communitysurvey) {
        $content[$communitysurvey->id] = communitysurvey_page_view($communitysurvey, 'teaser');
    }

    return $content;
}
