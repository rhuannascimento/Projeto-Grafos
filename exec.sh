#!/bin/bash
rm -rf build && mkdir build && g++ -g main.cpp ./src/*.cpp -o ./build/main && ./build/main instancias_grafos_n_ponderados/ex1.txt output_file.txt 1 0 X