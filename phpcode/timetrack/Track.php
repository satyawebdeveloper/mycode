
<div style="margin-left:50px;">
<?php
// $currentDate=date('Y-m-d h:i a');

// $date = new DateTime($currentDate, new DateTimeZone('Europe/Paris'));
// //date_default_timezone_set('America/New_York');
// echo date("Y-m-d h:i A", $date->format('U'));

// exit();
date_default_timezone_set("Asia/Calcutta");
$t1=strtotime(date('d-m-Y h:i a',"06-03-2014 12:00 PM"));
$t2=strtotime(date('d-m-Y h:i a',"07-03-2014 01:00 PM"));



$datetime1 = new DateTime("2014-03-07 23:00");
$datetime2 = new DateTime("2014-03-06 16:00");
$interval = $datetime1->diff($datetime2);
$hours   = $interval->format('%h');
$minutes = $interval->format('%i');
//echo 'Diff. in minutes is: '.($hours * 60 + $minutes);

echo $hours.':'.$minutes;
//7:0

exit();



date_default_timezone_set("Asia/Calcutta");
echo "India Date N Time :".date('d-m-Y h:i a',time());
//India Date N Time :06-03-2014 07:31 pm

date_default_timezone_set("America/New_York");
echo "<br/> America Newyork Date N Time :".date('d-m-Y h:i a',time());
//America Newyork Date N Time :06-03-2014 09:01 am




//echo date_default_timezone_get();
exit();

?>
<p>
   for different timezone refer
   <a href="http://www.php.net/manual/en/timezones.php" target="_blank">PHP TimeZone</a>
</p>
</div>

<?php 

$startDate=date("d-m-Y","07-03-2014"); //2014-01-31
$unixtmstmp=strtotime($startDate);


echo @$unixtmstmp;
exit();



$difference = strtotime() - strtotime($now);
$hours = $difference / 3600; // 3600 seconds in an hour
$minutes = ($hours - floor($hours)) * 60;
$final_hours = round($hours,0);
$final_minutes = round($minutes);



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
