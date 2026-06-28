/**
 * @file      gerador_de_grafo.hpp
 * @authors   Kaiky França dos Reis Silva and Samuel Horta de Faria
 * @brief     Declaration of function responsible for reading a file and instantiating the graphs in memory.
 * @version   0.1
 * @date      2026-06-27
 * @copyright Copyright (c) 2026 Kaiky França dos Reis Silva
 */


#ifndef GERADOR_DE_GRAFO_HPP
#define GERADOR_DE_GRAFO_HPP

#include "../lib/Graph_adjList.hpp"
#include "../lib/Graph_adjMatrix.hpp"

/**
 * @brief              Reads a text file and builds the graphs representations.
 * @param nome_arquivo Path/name of the text file containing the data of the graph.
 * @param gMatrix      Pointer passed by reference that will store the graph in a adjacency matrix format.
 * @param gList        Pointer passed by reference that will store the graph in a adjacency list format.
 * @return bool        Returns true if the graph was successfully built, or false in case the file couldn't be opened.
 */

bool gerar_Grafos(const char* nome_arquivo, Graph_adjMatrix*& gMatrix, Graph_adjList*& gList);

#endif