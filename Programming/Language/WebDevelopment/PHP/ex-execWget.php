<?php
	$file = 'EICAR';
	$dst = '/tmp';
	$download = false;

	exec("wget -t 1 -P $dst http://192.168.0.1/$file", $result);

	echo "<pre>";
	exec("ls -l $dst/$file", $result);
	for($i=0; $i<count($result); $i++)
	{
		print $result[$i]."\n";
		if (strpos($result[$i], "$file") != false)
		{
			$download = true;
		}
	}
	echo "</pre>\n";
	flush();

	if ($download == true)
	{
		echo '<div id="result">Accept</div>';
		exec("rm -f $dst/$file", $result);
	}
	else
	{
		echo '<div id="result">Block</div>';
	}
?>
