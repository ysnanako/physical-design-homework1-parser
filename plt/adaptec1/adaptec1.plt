set nokey
set term pngcairo font 'qt'
set output 'adaptec1/adaptec1.png'

set size ratio -1
set xrange [0:]
set yrange [0:]
plot[:][:] '../dat/adaptec1/adaptec1_chip.dat' w l lc -1, '../dat/adaptec1/adaptec1_cell.dat' w l lc 6, '../dat/adaptec1/adaptec1_pad.dat' w l lc 4, '../dat/adaptec1/adaptec1_pad_pin.dat' w l lc -1


set title 'adaptec1, MODULE= 210904, NET= 221142, HPWL= 7.12273e+07, ' font 'Times, 22'

set term qt
set key

set size ratio -1
plot[:][:] '../dat/adaptec1/adaptec1_chip.dat' w l lc -1, '../dat/adaptec1/adaptec1_cell.dat' w l lc 6, '../dat/adaptec1/adaptec1_pad.dat' w l lc 4, '../dat/adaptec1/adaptec1_pad_pin.dat' w l lc -1


pause -1 'Press any key'
