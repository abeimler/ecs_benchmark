# Scale font and line width (dpi) by changing the size! It will always display stretched.
set terminal png size 1280,720 enhanced font "Arial,12"
set output 'eventbus.png'

# Key means label...
set key inside bottom right
set xlabel 'Entities'
set ylabel 'Time per Operation (ns/op)'
set title 'ECS Benchmark Eventbus'

set logscale x 2
set logscale y 10
set format x "2^{%L}"
set format y "10^{%L}"

## the labels are in Alphabetical order
plot  "data-eventbus.dat" using 1:2 title 'entityx-eventbus' with lines lw 3 ,   "data-eventbus.dat" using 1:3 title 'eventpp-eventbus' with lines lw 3 ,  
