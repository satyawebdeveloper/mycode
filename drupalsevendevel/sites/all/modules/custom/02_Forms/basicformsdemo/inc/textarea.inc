<?php
function textareademopage() {
	return drupal_get_form("textarea_form");

}

function textarea_form($form, &$form_state) {
	$form = array();

	$form['comments'] = array(
	'#type'=>'textarea',
	'#title'=>'Comments',
	);
	
	
	return $form;
}
