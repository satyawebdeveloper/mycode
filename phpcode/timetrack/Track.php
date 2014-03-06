<?php

if(isset($_GET['gettime'])){
	echo @date('d-m-Y h:i:a',time());

	exit();
}


class UserDateNTimeTrack{
	
	public $login;
	public $logout;
	
	
}

?>

<!DOCTYPE html>
<html>
<head>
<script>
function checkTime(action)
{
var xmlhttp;    

if (window.XMLHttpRequest)
  {// code for IE7+, Firefox, Chrome, Opera, Safari
  xmlhttp=new XMLHttpRequest();
  }
else
  {// code for IE6, IE5
  xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
  }
xmlhttp.onreadystatechange=function()
  {
  if (xmlhttp.readyState==4 && xmlhttp.status==200)
    {
    document.getElementById(action).value=xmlhttp.responseText;
    }
  }
xmlhttp.open("GET","Track.php?gettime=time",true);
xmlhttp.send();
}
</script>
</head>
<body>

<form action=""> 
<input type="text" name="login" id="login">
<input type="button" value="check" onclick="checkTime('login')"> <br/>


<input type="text" name="logout" id="logout">
<input type="button" value="check" onclick="checkTime('logout')"> <br/>


<input type="text" name="breakin" id="breakin">
<input type="button" value="check" onclick="checkTime('breakin')"> <br/>


<input type="text" name="breakout" id="breakout">
<input type="button" value="check" onclick="checkTime('breakout')"> <br/>


<input type="submit" value="submit">




	


</form>
<br>

</body>
</html>
