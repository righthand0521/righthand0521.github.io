[Metasploit](https://www.metasploit.com/)
===
### [metasploit-framework](https://github.com/rapid7/metasploit-framework)
```
# curl https://raw.githubusercontent.com/rapid7/metasploit-omnibus/master/config/templates/metasploit-framework-wrappers/msfupdate.erb > msfinstall
# chmod 755 msfinstall
# ./msfinstall
```
---
```
# apt-get install postgresql postgresql-contrib -y
# service --status-all
# update-rc.d postgresql enable
# msfdb init
# msfdb reinit
```
```
searchsploit(1) - Exploit Database Archive Search
```
---
```
# msfconsole
msf > show options
msf > db_status
msf > db_rebuild_cache
msf > search samba
msf > show options
```
```
# msfconsole
msf > use auxiliary/scanner/portscan/syn
msf > show options
msf > set RHOSTS 192.168.0.0/24
msf > set PORTS 445
msf > run
```
```
# msfconsole
msf > use scanner/smb/smb_version
msf > show options
msf > set RHOSTS 192.168.0.0/24
msf > run
```
```
SMB Version Detection

# echo use auxiliary/scanner/smb/smb_version >> meterpreter.rc
# echo info >> meterpreter.rc
# echo set RHOSTS 192.168.0.0/24 >> meterpreter.rc
# echo show options >> meterpreter.rc
# echo run >> meterpreter.rc
# echo >> meterpreter.rc
# echo exit >> meterpreter.rc
# msfconsole -r meterpreter.rc
```
---
