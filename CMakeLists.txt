cmake_minimum_required(VERSION 3.10)
project(ProjetoGraph VERSION 1.0)

# Define o padrão C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adiciona flags de compilação equivalentes ao seu -Wall -Wextra
if(MSVC)
    # Flags específicas para o compilador do Visual Studio
    add_compile_options(/W4)
else()
    # Flags para GCC/Clang (Linux/MinGW)
    add_compile_options(-Wall -Wextra)
endif()

# Lista seus arquivos fonte
set(SOURCES 
    src/main.cpp 
    src/lib/Graph_adjList.cpp 
    src/lib/Graph_adjMatrix.cpp
)

# Cria o executável
add_executable(programa ${SOURCES})
