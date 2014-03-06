<?php

/**
 * Menu callback; List all communitysurvey types available.
 */
function communitysurvey_overview_types() {
    foreach (communitysurvey_types() as $type => $info) {
        $type_url_str = str_replace('_', '-', $type);
        $label = t('View @type', array('@type' => $info->name));
        $items[] = l($label, 'admin/structure/communitysurvey/manage/' . $type_url_str);
    }

    return theme('item_list', array('items' => $items));
}

/**
 * Menu callback; user Adress information page.
 *
 * @param object $communitysurvey_type
 */
function communitysurvey_information($communitysurvey_type) {
    return $communitysurvey_type->name . ': ' . $communitysurvey_type->description;
}
