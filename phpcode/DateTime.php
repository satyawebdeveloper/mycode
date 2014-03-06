<?php

$currentTime=time();
$t1="1391088600";
$t2="1391175000";


$r=$t2-$t1;

var_dump($r);
exit();



$d="2014-01-31";
$t="4:30 PM";
$u=$d." ".$t;
$unixt=strtotime($u);

var_dump($unixt);
exit();



$addhrs=$unixt+(100*60*60);







var_dump($addhrs);
exit();


$date = new DateTime('2014-02-31 00:00:00');
echo $date->format('Y-m-d H:i:s') . "<br>";
$date->add(new DateInterval('PT1H'));
echo $date->format('Y-m-d H:i:s') . "\n";