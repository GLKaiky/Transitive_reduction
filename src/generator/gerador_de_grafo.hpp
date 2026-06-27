#ifndef GERADOR_DE_GRAFO_HPP
#define GERADOR_DE_GRAFO_HPP

#include "../lib/Graph_adjList.hpp"
#include "../lib/Graph_adjMatrix.hpp"

bool gerar_Grafos(const char* nome_arquivo, Graph_adjMatrix*& gMatrix, Graph_adjList*& gList);

#endif