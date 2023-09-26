cmake_minimum_required(VERSION 3.12)

project(Projeto-Grafos)

set(CMAKE_C_COMPILER "D:/mingw/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "D:/mingw/bin/g++.exe")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(main 
    main.cpp
    src/Grafo.cpp
    src/No.cpp
    src/Aresta.cpp
)

# Include the include directories
target_include_directories(main PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(CMAKE_GENERATOR_PLATFORM x64)
set(CMAKE_GENERATOR_TOOLSET "host=x64")