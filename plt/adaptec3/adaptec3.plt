set nokey
set term pngcairo font 'qt'
set output 'adaptec3/adaptec3.png'

set size ratio -1
set xrange [0:]
set yrange [0:]
plot[:][:] '../dat/adaptec3/adaptec3_chip.dat' w l lc -1, '../dat/adaptec3/adaptec3_cell.dat' w l lc 6, '../dat/adaptec3/adaptec3_pad.dat' w l lc 4, '../dat/adaptec3/adaptec3_pad_pin.dat' w l lc -1


set title 'adaptec3, MODULE= 450927, NET= 466758, HPWL= 1.883e+08, ' font 'Times, 22'

set term qt
set key

set size ratio -1
plot[:][:] '../dat/adaptec3/adaptec3_chip.dat' w l lc -1, '../dat/adaptec3/adaptec3_cell.dat' w l lc 6, '../dat/adaptec3/adaptec3_pad.dat' w l lc 4, '../dat/adaptec3/adaptec3_pad_pin.dat' w l lc -1


pause -1 'Press any key'
