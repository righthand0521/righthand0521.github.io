#!/bin/sh

# apt install gnuplot-nox -y

[ -e "mem.log" ] && rm mem.log
[ -e "mem.png" ] && rm mem.png
while true; do
	free -m | grep Mem >> mem.log

	gnuplot showFreeMem.plt
	sleep 1
done

exit 0
