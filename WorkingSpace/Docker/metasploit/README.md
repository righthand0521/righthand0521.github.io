# [Metasploit](https://www.metasploit.com/)

## [metasploit-framework](https://github.com/rapid7/metasploit-framework)

```bash
curl https://raw.githubusercontent.com/rapid7/metasploit-omnibus/master/config/templates/metasploit-framework-wrappers/msfupdate.erb > msfinstall
chmod 755 msfinstall
./msfinstall
```

```bash
apt-get install postgresql postgresql-contrib -y
service --status-all
update-rc.d postgresql enable
msfdb init
msfdb reinit
```

## [Metasploitable](https://sourceforge.net/projects/metasploitable/)

ID: msfadmin
PW: msfadmin

```bash
sudo poweroff
```

## msfconsole

```bash
# msfconsole
msf > show options
msf > db_status
msf > db_rebuild_cache
msf > search samba
msf > show options
```

```bash
# msfconsole
msf > use auxiliary/scanner/portscan/syn
msf > show options
msf > set RHOSTS 192.168.0.0/24
msf > set PORTS 445
msf > run
```

```bash
# msfconsole
msf > use scanner/smb/smb_version
msf > show options
msf > set RHOSTS 192.168.0.0/24
msf > run
```

### msfconsole -r meterpreter.rc

```bash
echo use auxiliary/scanner/smb/smb_version >> meterpreter.rc
echo info >> meterpreter.rc
echo set RHOSTS 192.168.0.0/24 >> meterpreter.rc
echo show options >> meterpreter.rc
echo run >> meterpreter.rc
echo >> meterpreter.rc
echo exit >> meterpreter.rc

msfconsole -r meterpreter.rc
```

## Fix Fail Question

### [Started getting warnings apt repo on kali about apt-key deprication. Any ideas?](https://github.com/rapid7/metasploit-framework/issues/16263)

```bash
W: http://downloads.metasploit.com/data/releases/metasploit-framework/apt/dists/kali/InRelease:
Key is stored in legacy trusted.gpg keyring (/etc/apt/trusted.gpg), see the DEPRECATION section in apt-key(8) for details.

wget http://apt.metasploit.com/metasploit-framework.gpg.key
gpg --no-default-keyring --keyring ./metasploit-framework_keyring.gpg --import metasploit-framework.gpg.key
gpg --no-default-keyring --keyring ./metasploit-framework_keyring.gpg --export > ./metasploit-framework.gpg
mv ./metasploit-framework.gpg /etc/apt/trusted.gpg.d/
apt update
```
