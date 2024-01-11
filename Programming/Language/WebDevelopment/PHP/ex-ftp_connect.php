<?php
	// echo quit | ftp -A speedtest.tele2.net
	$ftp = ftp_connect("speedtest.tele2.net");
	if (!$ftp)
	{
		echo '<div id="result">Block</div>';
	}
	else
	{
		echo '<div id="result">Accept</div>';
		ftp_close($ftp); 
	}

	flush();
?>
