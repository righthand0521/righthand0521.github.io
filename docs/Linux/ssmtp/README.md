SMTP - Simple Mail Transfer Protocol
===
```
smtp.gmail.com  TLS 587
msa.hinet.net   NO  25
```
### [ssmtp(8), sendmail - send a message using smtp](https://linux.die.net/man/8/ssmtp)
```
# apt install ssmtp -y
```
```
# vim /etc/ssmtp/ssmtp.conf

hostname=192.168.0.1
root=<gmail address>
mailhub=smtp.gmail.com:587
FromLineOverride=YES
AuthUser=<gmail address>
AuthPass=<gmail password>
UseTLS=YES
UseSTARTTLS=YES
Debug=YES
```
```
# hostname --fqdn
# vim /etc/hosts
127.0.0.1    U20x64
```
---
```
# echo 'From: <Sender Email Address>' >> mail.txt
# echo 'To: <Receiver Email Address>' >> mail.txt
# echo 'Subject: Sending Email Using Curl' >> mail.txt
# curl -v --insecure "smtp://msa.hinet.net:25" --mail-from "<Email Address>" --mail-rcpt "<Email Address>" -T mail.txt
# rm mail.txt
```
```
# echo "email using the command line" | ssmtp <Email Address>
```
```
# [ -e "test.mail" ] && rm test.mail
# echo "To: <Email Address>" >> test.mail
# echo "From: <Email Address>" >> test.mail
# echo "Subject: Test" >> test.mail
# echo "This is a test for sending email" >> test.mail
# ssmtp -v <Email Address> < test.mail
# [ -e "test.mail" ] && rm test.mail
```
```
# apt install sharutils -y
# echo -e "to: <Email Address>\nsubject: Test\n" | (cat - && uuencode <Local Attached File Path> <Email Attached File Name>) | ssmtp <Email Address>
# uuencode <Local Attached File Path> <Email Attached File Name> | ssmtp <Email Address>
```
```
# apt install mpack -y
# mpack -s "<Subject>" <Local Attached File Path> <Email Address>
# echo "This is a test for sending email" >> test.mail; mpack -s "<Subject>" -d test.mail <Local Attached File Path> <Email Address>
```
---
