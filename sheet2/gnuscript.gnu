
set terminal png enhanced font 'Verdana,10'
set output 'gif-frames/009.png'
# Line width of the axes
set border linewidth 1.5
# Line styles
set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2
a=10
f(x) = exp(-a*x)
plot f(x) title '{e^{-10 x}}' with lines linestyle 1
set xlabel '{/Helvetica-Oblique x}'
set ylabel '{/Helvetica-Oblique f(x)}'
set xrange [0:10]
set yrange [0:10000]
set ytics ()

