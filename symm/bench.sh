#!/bin/bash

python3 symm_ultimate.py

g++ test.cpp -lopenblas g++ test.cpp -lopenblas -o symm -fpermissive

./symm 256