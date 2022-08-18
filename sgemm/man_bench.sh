#!/bin/bash

python3 modular_sgemm.py
g++ test.cpp -lopenblas -o sgemm -fpermissive
./sgemm 1024
