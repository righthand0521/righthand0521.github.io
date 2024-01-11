# SMTP - Simple Mail Transfer Protocol

- smtp.gmail.com
- smtp.live.com
- smtp.outlook.com
- msa.hinet.net

## [ssmtp(8), sendmail - send a message using smtp](https://linux.die.net/man/8/ssmtp)

```bash
# apt install ssmtp -y

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

# hostname --fqdn

# vim /etc/hosts
127.0.0.1    U20x64
```

```bash
echo "email using the command line" | ssmtp <Email Address>
```

```bash
[ -e "test.mail" ] && rm test.mail
echo "To: <Email Address>" >> test.mail
echo "From: <Email Address>" >> test.mail
echo "Subject: Test" >> test.mail
echo "This is a test for sending email" >> test.mail
ssmtp -v <Email Address> < test.mail
[ -e "test.mail" ] && rm test.mail
```

### sharutils

```bash
apt install sharutils -y
```

```bash
echo -e "to: <Email Address>\nsubject: Test\n" | \
(cat - && uuencode <Local Attached File Path> <Email Attached File Name>) | \
ssmtp <Email Address>

uuencode <Local Attached File Path> <Email Attached File Name> | ssmtp <Email Address>
```

## [mpack(1) - pack a file in MIME format](https://linux.die.net/man/1/mpack)

```bash
apt install mpack -y
```

```bash
mpack -s "<Subject>" <Local Attached File Path> <Email Address>
echo "This is a test for sending email" >> test.mail
mpack -s "<Subject>" -d test.mail <Local Attached File Path> <Email Address>
```

## curl

```bash
[ -e mail.txt ] && rm -f mail.txt
printf "From: <Sender Email Address>\n" >> mail.txt
printf "To: <Receiver Email Address>\n" >> mail.txt
printf "Subject: Sending Email Using Curl\n" >> mail.txt
printf "Content-Type: text/html; charset=\"utf-8\"\n" >> mail.txt
printf "<html><body><pre>\n" >> mail.txt
printf "Hello, world.\n" >> mail.txt
printf "</pre></body></html>\n" >> mail.txt
curl -v --insecure "smtp://msa.hinet.net:25" --mail-from "<Email Address>" --mail-rcpt "<Email Address>" -T mail.txt
[ -e mail.txt ] && rm -f mail.txt
```

```bash
curl -v --insecure "smtp://msa.hinet.net:25" --mail-from "Email Address" --mail-rcpt "Email Address" \
-F '=(;type=multipart/alternative' \
-F '=plain text message' -F '= <body>Hello, world.<br>curl</body>;type=text/html' -F '=)' \
-F '=@test.log' \
-H "Subject: Sending Email Using Curl" -H "From: Name <Email Address>" -H "To: Name <Email Address>"
```

- [curl : send html email with embedded image and attachment](https://stackoverflow.com/questions/44728855/curl-send-html-email-with-embedded-image-and-attachment)

```bash
#!/bin/sh

sesAccess='id'
sesSecret='pw'
sesFromName="Sender"
sesFromAddress="Sender@mail.com"
sesToName="Receiver"
sesToAddress="Receiver@mail.com"
sesSubject="Test Email from Script"
sesSMTP="smtp server"
sesPort="465"
sesMessage=$'Hello, world.\nTest'
sesFile="$1"
sesMIMEType=`file --mime-type "$sesFile" | sed 's/.*: //'`

curl -v --url smtps://$sesSMTP:$sesPort \
--ssl-reqd --mail-from $sesFromAddress --mail-rcpt $sesToAddress --user $sesAccess:$sesSecret \
-F '=(;type=multipart/mixed' -F "=$sesMessage;type=text/plain" \
-F "file=@$sesFile;type=$sesMIMEType;encoder=base64" -F '=)' \
-H "Subject: $sesSubject" -H "From: $sesFromName <$sesFromAddress>" -H "To: $sesToName <$sesToAddress>"
```

## openssl

- [base64encode](https://www.base64encode.org/)

```bash
# openssl s_client -starttls smtp -connect smtp.gmail.com:587 -crlf -ign_eof
EHLO smtp.gmail.com
AUTH LOGIN
gmail address of base64 encode
gmail password of base64 encode
MAIL FROM:<Sender Email Address>
RCPT TO:<Receiver Email Address>
DATA
SUBJECT:<Hello, world.>
Hello, world.
.
quit
```

```bash
# openssl s_client -starttls smtp -connect smtp.outlook.com:587 -crlf -ign_eof
EHLO smtp.outlook.com
AUTH LOGIN
hotmail address of base64 encode
hotmail password of base64 encode
MAIL FROM:<Sender Email Address>
RCPT TO:<Receiver Email Address>
DATA
SUBJECT:<Hello, world.>
Hello, world.
.
quit
```

## telnet

```bash
# telnet <SMTP Server> 25
EHLO <SMTP Server>
MAIL FROM:<Sender Mail>
RCPT TO:<Receiver Mail>
DATA
SUBJECT:Hello, world.

Hello, world.
.
quit
```
