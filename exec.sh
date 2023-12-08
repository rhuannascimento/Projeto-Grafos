#!/bin/bash
rm -rf build && mkdir build && g++ -std=c++17 -g main.cpp ./src/*.cpp -o ./build/main && ./build/main instancias_grafo_ponderados/100.txt output_file.txt 0 1 0