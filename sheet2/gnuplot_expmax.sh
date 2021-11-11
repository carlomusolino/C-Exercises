#!/bin/bash
for A in $(seq 1 10)
do
    printf -v i "%03d" $((A -1))
     export GNUSCRIPT="
set terminal png enhanced font 'Verdana,10'
set output 'gif-frames/${i}.png'
# Line width of the axes
set border linewidth 1.5
# Line styles
set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2
a=${A}
f(x) = exp(-a*x)
plot f(x) title '{e^{-${A} x}}' with lines linestyle 1
set xlabel '{/Helvetica-Oblique x}'
set ylabel '{/Helvetica-Oblique f(x)}'
set xrange [0:10]
set yrange [0:10000]
set ytics ()
"
     echo "${GNUSCRIPT}" > gnuscript.gnu
     gnuplot gnuscript.gnu
done 

