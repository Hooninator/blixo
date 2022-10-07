#!/bin/bash
echo "int main(){return 0;}" > sgemm.c
python3 modular_sgemm.py
clang sgemm.c -o sgemm -O3
objdump -d sgemm > assembly_clang_large.txt
gcc sgemm.c -o sgemm -O3
objdump -d sgemm > assembly_gnu_large.txt
g++ test.cpp -o sgemm_bench -fpermissive -Ofast #-finline-functions
./sgemm_bench 1024
#clang++ test.cpp -lopenblas -o sgemm_bench -fpermissive
#./sgemm_bench 768
