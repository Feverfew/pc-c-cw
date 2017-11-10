set xrange[0:6.3]
set yrange[-2:2]
plot "data.dat" with lines, sin(x)
pause 0.01
reread
