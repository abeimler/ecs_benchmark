# Scale font and line width (dpi) by changing the size! It will always display stretched.
set terminal png size 1024,800 enhanced font "Arial,14"
set output 'eventbus-result.png'

# Key means label...
set key inside bottom right
set xlabel 'Publish Events'
set ylabel 'Time per Operation (ns/op)'
set title 'Eventbus Benchmark'

set logscale x 2
set logscale y 10
set format x "2^{%L}"
set format y "10^{%L}"

plot "data-eventbus.dat" using 1:2 title 'EntityX1' with lines, \
	"data-eventbus.dat" using 1:3 title 'Eventpp' with lines

