<?php
if(isset($_POST['niceedit'])){


$con=mysqli_connect("localhost","root","","test");
// Check connection
if (mysqli_connect_errno())
{
	echo "Failed to connect to MySQL: " . mysqli_connect_error();
}

$qry="INSERT INTO niceedit (data) VALUES('". $_POST["area1"]."')";
$res=mysqli_query($con,$qry);
//var_dump($qry);

mysqli_close($con);

}

?> 

<html>
<head>
	<title>Demo 1 : Convert All Textareas</title>
</head>
<body>

<div id="menu"></div>

<div id="intro">
By calling the nicEditors.allTextareas() function the below example replaces all 3 textareas on the page with nicEditors. NicEditors will match the size of the editor window with the size of the textarea it replaced.
</div>
<br />

<div id="sample">
<script type="text/javascript" src="../nicEdit.js"></script>
<script type="text/javascript">
	bkLib.onDomLoaded(function() { nicEditors.allTextAreas() });
</script>



<form action="TestNiceEdit.php" method="post">
<h4>First Textarea</h4>
<textarea name="area1" cols="40"></textarea>
<input type="submit" name="niceedit">
</form>


</body>
</html>


