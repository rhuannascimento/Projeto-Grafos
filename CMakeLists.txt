
project(Projeto-Grafos)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp
        ./src/Grafo.cpp
        ./include/Grafo.h
        ./include/No.h
        ./include/Aresta.h
        )