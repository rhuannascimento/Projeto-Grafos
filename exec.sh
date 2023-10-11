#!/bin/bash
rm -rf build && mkdir build && g++ -g main.cpp ./src/*.cpp -o ./build/main && ./build/main 1 1 ex1.txt

