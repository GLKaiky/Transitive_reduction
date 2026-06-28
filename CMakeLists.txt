cmake_minimum_required(VERSION 3.10)
project(ProjetoGraph VERSION 1.0)

# Define o padrão C++ exigido (C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configurações de Compilação (O divisor de águas Windows vs Linux)
if(MSVC)
    # Compilador da Microsoft (Visual Studio / Windows nativo)
    # /W4: Equivalente ao -Wall e -Wextra
    # /utf-8: Impede o Windows de quebrar os acentos em pt-BR (Salva vidas!)
    add_compile_options(/W4 /utf-8)
else()
    # Compiladores GCC/Clang (Linux, Mac, ou Windows via MinGW)
    add_compile_options(-Wall -Wextra -g)
endif()

# Lista de arquivos fonte (Adicione o gerador de grafos aqui se for usar)
set(SOURCES 
    src/main.cpp 
    src/lib/Graph_adjList.cpp 
    src/lib/Graph_adjMatrix.cpp
    src/generator/gerador_de_grafo.cpp
    src/benchmark/runner.cpp
)

# Cria o executável
add_executable(programa ${SOURCES})

# Avisa ao compilador onde procurar os arquivos .hpp
# Isso permite que no main.cpp você use #include "lib/Graph_adjMatrix.hpp" sem dar erro.
target_include_directories(programa PRIVATE src)