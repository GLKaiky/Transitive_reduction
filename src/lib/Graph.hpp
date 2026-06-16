/**
 * @file      Graph.hpp
 * @author    Kaiky França dos Reis Silva
 * @brief     Defines the "Grafo" header
 * @version   0.1
 * @date      2026-06-15
 * @copyright Copyright (c) 2026 Kaiky França dos Reis Silva
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <list>

    class Graph {
        private:
            unsigned int number_of_vertex;
            std::vector<std::list<int> > adjList; //Graph extructure

        public:
            //Constructor
            Graph(int number_of_vertex);

            //Add and Remove methods
            void addEdge(unsigned int origin, unsigned int destiny);
            void removeEdge(unsigned int origin, unsigned int destiny);

            //Transitive reduction method. The goal is to remove the reduntant edges
            void execute_transitive_reduction();

            void printGraph();


            void DFS(); // Deth First Search
 
            void BFS(); //Breadth First Search

    };

#endif