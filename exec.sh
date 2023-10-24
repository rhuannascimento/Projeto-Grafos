#!/bin/bash
rm -rf build && mkdir build && g++ -g main.cpp ./src/*.cpp -o ./build/main && ./build/main instancias_grafo_ponderados/ex1.txt X 1 1 X