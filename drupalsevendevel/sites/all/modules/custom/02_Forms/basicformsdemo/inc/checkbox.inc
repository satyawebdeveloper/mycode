<?php
function checkboxdemopage() {
	return drupal_get_form("checkbox_form");

}

function checkbox_form($form, &$form_state) {
	$form = array();

	 //Checkboxes
  $defaulthobbies = array();
    $defaulthobbies[]='Cricket';
    $defaulthobbies[]='TV';
   $form['hobbies'] = array(
  '#type' => 'checkboxes',
  '#options' => drupal_map_assoc(array(
     t('Cricket'),
     t('Chess)'),
     t('TV')
     )),
   '#title' => t('Hobbies'),
   '#default_value' => $defaulthobbies,
   );
	
	
	return $form;
}
