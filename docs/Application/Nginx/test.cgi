#!/bin/bash

echo -ne 'Status: 200\r\n'
echo -ne 'Content-Type: text/plain\r\n'
echo -ne '\r\n'

echo -e "${LINENO}: ${QUERY_STRING}"

exit 0
