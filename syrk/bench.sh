#!/bin/bash
python3 syrk.py

g++ test.cpp -lopenblas -o syrk

./syrk 16