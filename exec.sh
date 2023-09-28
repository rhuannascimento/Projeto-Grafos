#!/bin/bash
rm -rf build && mkdir build && g++ main.cpp ./src/*.cpp -o ./build/main && ./build/main 1

