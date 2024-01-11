<?php
	$ipaddress = '8.8.8.8';
	$option = '-w 3';
	$loss = false;

	echo "<pre>";
	exec("ping  $ipaddress $option", $list);
	for($i=0; $i<count($list); $i++)
	{
		print $list[$i]."\n";
		if (strpos($list[$i], "100% loss") != false)
		{
			$loss = true;
		}
	}
	echo "</pre>\n";
	flush();

	if ($loss == true)
	{
		echo '<div id="result">Block</div>';
	}
	else
	{
		echo '<div id="result">Accept</div>';
	}
?>
