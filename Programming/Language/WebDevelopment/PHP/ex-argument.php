<?php
	if (empty($_SERVER["HTTP_X_FORWARDED_FOR"]))
	{
		$client = $_SERVER["REMOTE_ADDR"];
	}
	else
	{
		$client = explode(",", $_SERVER["HTTP_X_FORWARDED_FOR"]);
		$client = $client[0];
	}
	print '<div id="clientIP">' . $client . '</div>' . PHP_EOL;

	if (isset($_SERVER['SERVER_ADDR']))
	{
		print '<div id="serverIP">' . $_SERVER['SERVER_ADDR'] . '</div>' . PHP_EOL;
	}

	// http://<IP Address>/<PHP Path>?argument1=<arg1>&argument2=<arg2>
	$argument1 = $_GET['argument1'];
	if (isset($argument1))
	{
		print '<div id="argument1">' . $argument1 . '</div>' . PHP_EOL;
	}

	$argument2 = $_GET['argument2'];
	if (isset($argument2))
	{
		print '<div id="argument2">' . $argument2 . '</div>' . PHP_EOL;
	}
?>
