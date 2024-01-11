#!/bin/sh

systemctl restart named
sleep 1
echo
echo "systemctl restart named"
echo "dig @127.0.0.1 -p 53 smb.dns.yc.org Any"
echo
bash

exit 0
