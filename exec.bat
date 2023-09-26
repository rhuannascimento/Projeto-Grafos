@echo off
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
main.exe