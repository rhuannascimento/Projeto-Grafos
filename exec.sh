#!/bin/bash
rm -rf build && mkdir build && g++ -g main.cpp ./src/*.cpp -o ./build/main && ./build/main

