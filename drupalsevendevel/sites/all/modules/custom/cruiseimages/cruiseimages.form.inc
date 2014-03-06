<?php
function cruiseimages_add() {
	$cruiseimages = ( object ) array (
			'id' => '',
			'card_id' => '',
			'flag' => '',
			'created' => '' 
	);
	
	return drupal_get_form ( 'cruiseimages_add_form', $cruiseimages );
}
function cruiseimages_add_form($form, &$form_state, $cruiseimages) {
	$formstatus = $cruiseimages->id == '' ? "add" : "edit";
	$form ['operation'] = array (
			'#type' => 'hidden',
			'#value' => $formstatus 
	);
	
	$auto_id = $cruiseimages->id != '' ? $cruiseimages->id : "";
	$form ['auto_id'] = array (
			'#type' => 'hidden',
			'#value' => $auto_id 
	);
	
	$form ['cardid'] = array (
			'#type' => 'textfield',
			'#title' => t ( 'Card ID' ),
			'#default_value' => isset ( $cruiseimages->card_id ) ? $cruiseimages->card_id : '' 
	);
	
// 	$form ['cruiseimg'] = array (
// 			'#type' => 'file',
// 			'#name' => 'cruiseimg',
// 			'#title' => t ( 'image' ),
// 			'#size' => 40,
// 			'#description' => t ( "" ) 
// 	);

	// Use the #managed_file FAPI element to upload an image file.
	$form['image_example_image_fid'] = array(
			'#title' => t('Image'),
			'#type' => 'managed_file',
			'#description' => t('The uploaded image will be displayed on this page using the image style choosen below.'),
			'#default_value' => variable_get('image_example_image_fid', ''),
			'#upload_location' => 'public://image_example_images/',
	);
	field_attach_form ( 'cruiseimages', $cruiseimages, $form, $form_state );
	$form ['submit'] = array (
			'#type' => 'submit',
			'#value' => t ( 'Save' ) 
	);
	return $form;
}
function cruiseimages_add_form_validate($form, &$form_state) {
	$cruiseimages = ( object ) $form_state ['values'];
	field_attach_form_validate ( 'cruiseimages', $cruiseimages, $form, $form_state );
}
function cruiseimages_add_form_submit($form, &$form_state) {
	
	if(isset($form_state['values']['cruiseimg'])){
		$validators = array('file_validate_extensions' => array('jpg jpeg'));
		$file = file_save_upload('cruiseimg', $validators, 'public://');
		if($file == false){
			drupal_set_message(t("Error saving image."), $type = "error", $repeat = false);
		}
		else{
			$file->status = FILE_STATUS_PERMANENT;
			$file = file_save($file);
		}
	}
	
	
	$card_id = $form_state ['values'] ['cardid'];
	$auto_id = $form_state ['values'] ['auto_id'];
	
	$cruiseimages = new stdClass ();
	$cruiseimages->id = $auto_id;
	$cruiseimages->card_id = $card_id;
	$cruiseimages->created = time ();
	$cruiseimages->flag = "0";
	field_attach_submit ( 'cruiseimages', $cruiseimages, $form, $form_state );
	$cruiseimages = cruiseimages_save ( $cruiseimages );
	
	$operation = $form_state ['values'] ['operation'];
	$msg = '';
	if ($operation == "add") {
		$msg = 'Gift Card Created Successfully.';
	} else {
		$msg = 'Gift Card Updated Successfully.';
	}
	
	drupal_set_message ( $msg );
	$form_state ['redirect'] = 'admin/structure/cruiseimages/manage';
}