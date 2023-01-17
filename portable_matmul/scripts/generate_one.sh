#!/bin/bash

echo "Generating $1 x $1 microkernel..."
python3 ../src/driver.py $1 $2
cp ../microkernels/$1x$1_microkernel.c ../tests/microkernel.c
echo "Copying microkernel to freddie..."
scp ../tests/microkernel.c jbellavita@freddie.millennium.berkeley.edu:~/exo_dev/portable_matmul
