# Scale font and line width (dpi) by changing the size! It will always display stretched.
set terminal png size 1024,800 enhanced font "Arial,14"
set output 'systems-update-result.png'

# Key means label...
set key inside bottom right
set xlabel 'Entities'
set ylabel 'Time per Operation (ns/op)'
set title 'ECS Benchmark System Updates'

set logscale x 2
set logscale y 10
set format x "2^{%L}"
set format y "10^{%L}"

## the labels are in Alphabetical order
plot  "data-systems-update.dat" using 1:2 title 'anaxupdate' with lines lw 3 ,   "data-systems-update.dat" using 1:3 title 'entityx1update' with lines lw 3 ,   "data-systems-update.dat" using 1:4 title 'entityx2update' with lines lw 3 ,   "data-systems-update.dat" using 1:5 title 'enttupdate' with lines lw 3 ,   "data-systems-update.dat" using 1:6 title 'ginsengupdate' with lines lw 3 ,  
