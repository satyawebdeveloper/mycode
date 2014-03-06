<!DOCTYPE html>
<html lang="<?php print $language->language; ?>">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1, user-scalable=no">
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <?php print $scripts; ?>
  <!-- HTML5 element support for IE6-8 -->
  <!--[if lt IE 9]>
    <script src="//html5shiv.googlecode.com/svn/trunk/html5.js"></script>
  <![endif]-->
  <?php
	if($user->name == "staffadmin" || $user->name == "agent"){
  ?>
  <link rel="stylesheet" type="text/css" href="<?php echo base_path().path_to_theme() ?>/css/staffadminstyle.css" />
  <?php
	}
  ?>
  <script src="<?php echo base_path() . path_to_theme() ?>/js/jquery-1.9.1.js"></script>
  
</head>
<body class="<?php print $classes; ?>" <?php print $attributes;?>>
  <?php print $page_top; ?>
  <?php print $page; ?>
  <?php print $page_bottom; ?>
    
  <script src="<?php echo base_path() . path_to_theme(); ?>/bootstrap/js/bootstrap-alert.js"></script>
  <script src="<?php echo base_path() . path_to_theme(); ?>/bootstrap/js/bootstrap-tooltip.js"></script>
  <script src="<?php echo base_path() . path_to_theme(); ?>/bootstrap/js/bootstrap-popover.js"></script>
  <script src="<?php echo base_path() . path_to_theme(); ?>/bootstrap/js/bootstrap-modal.js"></script>
  <script src="<?php echo base_path() . path_to_theme(); ?>/bootstrap/js/bootstrap-transition.js"></script>
  <script src="<?php echo base_path() . path_to_theme(); ?>/bootstrap/js/bootstrap-carousel.js"></script>
  <script src="<?php echo base_path() . path_to_theme(); ?>/bootstrap/js/hover-dropdown.js"></script>
  <script>
//    jQuery(document).ready(function() {
//      jQuery('.js-activated').dropdownHover().dropdown();
//    });

    $("#cruiseKeyPop").popover({
        //title: 'Popover on Top',
        html: true,
        trigger: 'click',
        content: function() {
            return $('#popover_content_wrapper').html();
        },
        placement: 'top'
    });

  </script>
    
</body>
</html>
