# hydra(1) - a very fast network logon cracker which supports many different services

## Install

```bash
apt install hydra -y
```

### [install Hydra v8.6 in Ubuntu 20](https://github.com/vanhauser-thc/thc-hydra)

```bash
apt install libssl-dev libssh-dev libidn11-dev libpcre3-dev libgtk2.0-dev libmysqlclient-dev libpq-dev libsvn-dev \
firebird-dev libmemcached-dev libgpg-error-dev libgcrypt20-dev -y

cd /opt
mkdir hydra

cd hydra
wget https://github.com/vanhauser-thc/thc-hydra/archive/8.6.tar.gz
tar -zxvf 8.6.tar.gz

cd thc-hydra-8.6
./configure
make
make install

ln -s /usr/local/bin/hydra /usr/bin/hydra
hydra
```

## Usage

```bash
hydra -V -f -l <UserName> -p <Password> <IP> <telnet|ftp|ssh|rdp>
hydra -V -f -l <UserName> -P <Password File> <IP> <telnet|ftp|ssh|rdp>
hydra -V -f -L <UserName File> -p <Password> <IP> <telnet|ftp|ssh|rdp>
hydra -V -f -L <UserName File> -P <Password File> <IP> <telnet|ftp|ssh|rdp>
hydra -V -f -t 5 -l <UserName> -P <Password File> <IP> <telnet|ftp|ssh|rdp>
hydra -V -f -t 5 -L <UserName File> -P <Password File> <IP> <telnet|ftp|ssh|rdp>

-l LOGIN or -L FILE  login with LOGIN name, or load several logins from FILE
-p PASS  or -P FILE  try password PASS, or load several passwords from FILE
-s PORT              if the service is on a different default port, define it here
-f / -F              exit when a login/pass pair is found (-M: -f per host, -F global)
-v / -V / -d         verbose mode / show login+pass for each attempt / debug mode
-t TASKS             run TASKS number of connects in parallel per target (default: 16)
-T TASKS             run TASKS connects in parallel overall (for -M, default: 64)
-w / -W TIME         wait time for a response (32) / between connects per thread (0)
```

```bash
hydra -V -f -l <UserName> -x 1:1:aA1 192.168.0.1 rdp

-x MIN:MAX:CHARSET   password bruteforce generation, type "-x -h" to get help
 MIN     is the minimum number of characters in the password
 MAX     is the maximum number of characters in the password
 CHARSET is a specification of the characters to use in the generation
            valid CHARSET values are: 'a' for lowercase letters,
            'A' for uppercase letters, '1' for numbers, and for all others,
            just add their real representation.
 -y         disable the use of the above letters as placeholders
 Examples:
  -x 3:5:a       generate passwords from length 3 to 5 with all lowercase letters
  -x 5:8:A1      generate passwords from length 5 to 8 with uppercase and numbers
  -x 1:3:/       generate passwords from length 1 to 3 containing only slashes
  -x 5:5:/%,.-   generate passwords with length 5 which consists only of /%,.-
  -x 3:5:aA1 -y  generate passwords from length 3 to 5 with a, A and 1 only
```

## Fix Fail Question

### hydra: error while loading shared libraries: libidn.so.11: cannot open shared object file: No such file or directory

```bash
locate libidn.so
cd /usr/lib/x86_64-linux-gnu
ls -l libidn.so*
ln -s libidn.so.12.6.3 libidn.so.11
ls -l libidn.so*
```
