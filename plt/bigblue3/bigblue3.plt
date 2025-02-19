set nokey
set term pngcairo font 'qt'
set output 'bigblue3/bigblue3.png'

set size ratio -1
set xrange [0:]
set yrange [0:]
plot[:][:] '../dat/bigblue3/bigblue3_chip.dat' w l lc -1, '../dat/bigblue3/bigblue3_cell.dat' w l lc 6, '../dat/bigblue3/bigblue3_pad.dat' w l lc 4, '../dat/bigblue3/bigblue3_pad_pin.dat' w l lc -1


set title 'bigblue3, MODULE= 1095514, NET= 1123170, HPWL= 2.97832e+08, ' font 'Times, 22'

set term qt
set key

set size ratio -1
plot[:][:] '../dat/bigblue3/bigblue3_chip.dat' w l lc -1, '../dat/bigblue3/bigblue3_cell.dat' w l lc 6, '../dat/bigblue3/bigblue3_pad.dat' w l lc 4, '../dat/bigblue3/bigblue3_pad_pin.dat' w l lc -1


pause -1 'Press any key'
