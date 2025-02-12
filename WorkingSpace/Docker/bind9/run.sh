#!/bin/sh

service named start
sleep 1
echo
echo "service named status"
echo "dig @127.0.0.1 -p 53 smb.dns.yc.org Any"
echo
bash

exit 0
