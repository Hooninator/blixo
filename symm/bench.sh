#!/bin/bash

python3 symm_ultimate.py

g++ test.cpp -lopenblas g++ test.cpp -lopenblas -o sgemm -fpermissive

./a.out 256