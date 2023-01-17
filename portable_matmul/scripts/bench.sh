#!/bin/bash
g++ ../tests/bench.cpp -o bench -lopenblas -l:libblis.a -fpermissive -O3
./bench $1 sgemm
rm bench