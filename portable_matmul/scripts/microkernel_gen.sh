#!/bin/bash

for i in $(seq 16 1 64) 
do
    echo "Generating $i x $i microkernel..."
    python3 ../src/driver.py $i $1
done
