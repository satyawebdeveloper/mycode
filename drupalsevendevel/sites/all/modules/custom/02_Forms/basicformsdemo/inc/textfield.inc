<?php
function textfieldpage() {
	return drupal_get_form("textfield_form");

}

function textfield_form($form, &$form_state) {
	$form = array();
	
// 	$form['date'] = array(
// 			//'#prefix'=>t('When do you want to start the featured campaign?'),
// 			//'#date_format' => 'Y-m-d',
// 			//'#date_year_range' => '0:+1',
// 			//'#type' => 'date_popup',
// 			'#type' => 'date',
// 			'#weight'=>0
// 	);

	$form['day']=array(
			'#type' => 'select',
			'#title' => t(''),
			'#options' => range ( 1, 31 ),
			'#empty_option' => t ( 'Day' )
			
	);
	
	
	$form ['month'] = array (
			'#type' => 'select',
			'#title' => '',
			'#options' => array (
					1 => t ( '01 - January' ),
					2 => t ( '02 - February' ),
					3 => t ( '03 - March' ),
					4 => t ( '04 - April' ),
					5 => t ( '05 - May' ),
					6 => t ( '06 - June' ),
					7 => t ( '07 - July' ),
					8 => t ( '08 - August' ),
					9 => t ( '09 - September' ),
					10 => t ( '10 - October' ),
					11 => t ( '11 - November' ),
					12 => t ( '12 - December' ) 
			),
			// '#default_value' => isset() ? $values['creditExpMonth'] : '',
			'#empty_option' => t ( 'Month' ) 
	);
	
	$min =intval(date('Y'));
	$max = intval(date('Y')) + -100;
	$form['year']=array(
			'#type' => 'select',
			'#options' => drupal_map_assoc(range($min, $max)),
			'#attributes' => array('placeholder' => t('ExpYear'), 'class' => array('selectFieldStyle selectFieldVerySmall')),
			'#default_value' => isset($values['creditExpYear']) ? $values['creditExpYear'] : '',
			'#empty_option' => t('Year'),
		
	);
	

	
	
	
	

// 	$form['username'] = array(
// 	'#type'=>'textfield',
// 	'#title'=>'User Name',
// 	);

// 	$dateformat = 'Y-m-d H:i';
// 	$form['ddd'] = array(
// 	'#type' => 'date_popup',
// 	//'#date_timezone' => date_default_timezone(),
// 	//'#date_format' => $dateformat,
// 	//'#date_year_range' => '-3:+3',
// 	//'#title' => 'asdf',
// 	//'#default_value' => '',
// 	//'#required' => TRUE,
// 			);
	
	
	
// 	$form['birthdate'] = array(
// 			'#title' => t('Birthdate'),
// 			'#type' => 'date',
// 			'#description' => t('Select your birthdate'),
// 			'#default_value' => array(
// 					'month' => format_date(time(), 'custom', 'n'),
// 					'day' => format_date(time(), 'custom', 'j'),
// 					'year' => format_date(time(), 'custom', 'Y'),
// 			),
// 	);
	
	return $form;
}
