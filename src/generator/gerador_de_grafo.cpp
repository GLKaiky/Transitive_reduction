/**
 * @file      gerador_de_grafo.cpp
 * @author    Kaiky França dos Reis Silva
 * @brief     
 * @version   0.1
 * @date      2026-06-27
 * @copyright Copyright (c) 2026 Kaiky França dos Reis Silva
 */


#include "gerador_de_grafo.hpp"
#include <fstream>
#include <iostream>

bool gerar_Grafos(const char* nome_arquivo, Graph_adjMatrix*& gMatrix, Graph_adjList*& gList) {
    std::ifstream arquivo(nome_arquivo);
    
    if (!arquivo.is_open()) {
        return false;
    }

    unsigned int num_vertices;
    arquivo >> num_vertices;

    gMatrix = new Graph_adjMatrix(num_vertices);
    gList = new Graph_adjList(num_vertices);

    unsigned int origem, destino;
    while (arquivo >> origem >> destino) {
        gMatrix->addEdge(origem, destino);
        gList->addEdge(origem, destino);
    }

    arquivo.close();
    return true;
}