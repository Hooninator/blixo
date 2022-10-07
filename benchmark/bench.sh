#!/bin/bash

g++ bench.cpp -o bench -lopenblas -l:libblis.a
for op in "sgemm" "syrk" "symm"
do
    rm stats.out
    touch stats.out
    for i in $(seq 4 1 64)
    do
        echo "$i"
        ./bench $i $op
    done
    python3 bench.py -o $op
done