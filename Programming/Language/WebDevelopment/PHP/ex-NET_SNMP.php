<?php
	class NET_SNMP {
		private $host = "127.0.0.1";
		private $community = "public";

		function func_snmpget($oid) {
			if (!isset($this))
			{
				print __CLASS__ . " is not defined." . PHP_EOL;
				return;
			}
			print htmlspecialchars(snmpget($this->host, $this->community, $oid), ENT_QUOTES) . PHP_EOL;
		}
		function func_snmpwalk($oid) {
			if (!isset($this))
			{
				print __CLASS__ . " is not defined." . PHP_EOL;
				return;
			}
			print_r(snmpwalk($this->host, $this->community, $oid));
		}
	}

	$classVar = new NET_SNMP;
	$classVar->func_snmpget("1.3.6.1.2.1.1.1.0");
	$classVar->func_snmpwalk("1.3.6.1.2.1.1.9.1.2");
?>
