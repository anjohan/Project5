#!/bin/bash

end_t=0.5
dxs=(0.1 0.01)
methods=("forward_Euler" "backward_Euler" "Crank_Nicolson")

for dx in ${dxs[*]}; do
    for method in ${methods[*]}; do
        dt=`bc -l <<< "0.5*$dx^2"`
        dn=`python -c "print int($end_t/$dt*0.1)"`
        filename="${method}_$dx.dat"
        ./onedim_ui.x $filename $method $dt $end_t $dx $dn
        python transpose.py $filename transpose_$filename
    done
done
