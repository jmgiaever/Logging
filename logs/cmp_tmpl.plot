set terminal postscript color
set output "Logging/logs/compare.ps"
set autoscale
set xlabel "# avarage processing time, "work on" (ex. string lenth). -- Intel Core i7-2640M CPU @ 2.80GHz x 4 "
set ylabel "Time (microseconds) -- Intel Core i7-2640M CPU @ 2.80GHz x 4 "
set key right
plot \
"Logging/logs/log1.data" w linespoints lw 2 t "Implementation 1", \
"Logging/logs/log2.data" w linespoints lw 2 t "Implementation 2", \
"Logging/logs/log3.data" w linespoints lw 2 t "Implementation 3"