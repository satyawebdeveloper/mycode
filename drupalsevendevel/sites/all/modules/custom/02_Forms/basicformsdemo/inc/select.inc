<?php
function selectpage() {
	return drupal_get_form("select_form");

}

function select_form($form, &$form_state) {
	$form = array();

	//Drop Down
	$form['selected'] = array(
    '#type' => 'select',
    '#title' => t('Selected'),
    '#options' => array(
      0 => t('No'),
      1 => t('Yes'),
    ),
    '#default_value' => 0,
    '#description' => t('Set this to <em>Yes</em> if you would like this category to be selected by default.'),
  );
  
  $arr1=array('1'=>'One');
  $arr2=array('2'=>'Two');
  
  
  $arr3=array('3'=>'Three');
  $arr4=array('4'=>'Four');
  
  
  $arr5[]=$arr1;
  $arr5[]=$arr2;
  
  drupal_json_output($arr5);
  exit();
// $arr5=$arr1+$ar2;
 
  
  
  
  $form['selectdemo']=array(
  '#type'=>'select',
  '#options'=>$arr5,
  
  );
	
	return $form;
}
