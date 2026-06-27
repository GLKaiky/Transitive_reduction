/**
 * @file      gerador_de_grafo.hpp
 * @author    Kaiky França dos Reis Silva
 * @brief     
 * @version   0.1
 * @date      2026-06-27
 * @copyright Copyright (c) 2026 Kaiky França dos Reis Silva
 */


#ifndef GERADOR_DE_GRAFO_HPP
#define GERADOR_DE_GRAFO_HPP

#include "../lib/Graph_adjList.hpp"
#include "../lib/Graph_adjMatrix.hpp"

bool gerar_Grafos(const char* nome_arquivo, Graph_adjMatrix*& gMatrix, Graph_adjList*& gList);

#endif