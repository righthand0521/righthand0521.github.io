#!/usr/bin/env bash

echo "Content-type: text/html"
echo ""

echo "<html>"

echo "<head>"
echo "<title>ex-bash.cgi</title>"
echo "</head>"

echo "<body>"
echo "<h2>Hello, world!</h2>"
echo "Computer name : $HOSTNAME<br/>"
path="$(pwd)"
echo "The current path: ${path}<br/>"
echo "</body>"

echo "</html>"
