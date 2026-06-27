/**
 * @file      gerador_de_grafo.cpp
 * @authors   Kaiky França dos Reis Silva and Samuel Horta de Faria
 * @brief     Implementation of file reading function and and graph structures generation.
 * @version   0.1
 * @date      2026-06-27
 * @copyright Copyright (c) 2026 Kaiky França dos Reis Silva
 */


#include "gerador_de_grafo.hpp"
#include <fstream>
#include <iostream>

bool gerar_Grafos(const char* nome_arquivo, Graph_adjMatrix*& gMatrix, Graph_adjList*& gList) {
    
    //Tries to open the file in read mode.
    std::ifstream arquivo(nome_arquivo);
    
    //Checks if it was possible or not to open the file. Returns false if couldn't open it.
    if (!arquivo.is_open()) {
        return false;
    }

    //Reads the first line of the file, which contains the total number of vertices.
    unsigned int num_vertices;
    arquivo >> num_vertices;

    //Dynamically instantiates the graphs, both Matrix and List, using the read number of vertices.
    gMatrix = new Graph_adjMatrix(num_vertices);
    gList = new Graph_adjList(num_vertices);

    //Auxialary variables to store the origin and destination of each edge.
    unsigned int origem, destino;

    //Reads the file in a loop extracting pairs of values until the end of the file.
    while (arquivo >> origem >> destino) {
        gMatrix->addEdge(origem, destino);
        gList->addEdge(origem, destino);
    }

    //Closes the file and return success after finishing the construction of the graphs.
    arquivo.close();
    return true;
}