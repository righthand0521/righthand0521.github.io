set term png small size 800,600
set output "mem.png"
set title "free -m"
set ylabel "MB"
set ytics nomirror
set yrange [0:*]

plot "mem.log" using 2 with lines axes x1y1 title "total", \
     "mem.log" using 3 with lines axes x1y1 title "used", \
     "mem.log" using 4 with lines axes x1y1 title "free"
