#!/bin/bash
rm -rf build && mkdir build && g++ -std=c++17 -g main.cpp ./src/*.cpp -o ./build/main && ./build/main instancias_grafo_ponderados/ex1.txt output_file.txt 1 1 X