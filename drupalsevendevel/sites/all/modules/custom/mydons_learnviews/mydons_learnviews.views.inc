<?php

/**
 * @file
 * Views integration for the mydons custom module
 */

/**
 * Implements hook_views_data()
 *
 */
function mydons_learnviews_views_data() {

 $table = array(
    'mydons_customtable' => array(  // Mydons Custom table
       'table' => array(
          'group' => 'Mydons',      // Groupname Mydons
             'base' => array(
               'field' => 'mydons_custom_id',  //Primary key
               'title' => 'Mydons Customtable',
               'help' => 'Mydons Custom database table'
            )
        ),
     //Description of mydons_custom_id
        'mydons_custom_id' => array(  
           'title' => t('Mydons Custom Id'),
           'help' => t('Mydons Custom table  Id field'),
           // is mydons_custom_id field sortable TRUE
           'field' => array(
              'click sortable' => TRUE,  
            ),
      //Filter handler for filtering records by mydons_custom_id     
           'filter' => array(
               'handler' => 'views_handler_filter_numeric'   
            ),  

           'sort' => array(
              'handler' => 'views_handler_sort'       
           )
         ),
      //Description of mydons_custom_title field
        'mydons_custom_title' => array(      
           'title' => t('Mydons Custom Title'),
           'help' => t('Mydons Custom table  Title field'),
           'field' => array(
              'click sortable' => TRUE,
           ),
           'filter' => array(
              'handler' => 'views_handler_filter_string'
           ),

           'sort' => array(
              'handler' => 'views_handler_sort'
           )
        ),
     //Description of mydons_custom_body field
       'mydons_custom_body' => array(           
           'title' => t('Mydons Custom Body'),
           'help' => t('Mydons Custom table Body field'),
           'field' => array(
                'click sortable' => TRUE,
             ),
           'filter' => array(
                 'handler' => 'views_handler_filter_string'
             ),
          'sort' => array(
             'handler' => 'views_handler_sort'
          )
        )
      )
    );
    return $table;
}