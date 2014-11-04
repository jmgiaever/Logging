set terminal postscript color
set output "Logging/logs/compare.ps"
set autoscale
set xlabel "# avarage processing time. -- Intel Core i7-2640M CPU @ 2.80GHz x 4 "
set ylabel "Time (microseconds) -- Intel Core i7-2640M CPU @ 2.80GHz x 4 "
set key right
plot \
"Logging/logs/for.data" w linespoints lw 2 t "For-dummy algorithm", \
"Logging/logs/while.data" w linespoints lw 2 t "While-dummy algorithm"