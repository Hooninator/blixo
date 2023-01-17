#!/bin/bash

for i in $(seq 16 1 64)
do
	echo "Benchmarking $i x $i..."
	cp ../microkernels/${i}x${i}_microkernel.c ../tests/microkernel.c
    cd ../tests
	g++ bench.cpp -o bench -lopenblas -I /usr/local/include/blis -L /usr/local/lib/libblis.a  -fpermissive -O3 -l:libblis.a
	./bench $i sgemm
done
