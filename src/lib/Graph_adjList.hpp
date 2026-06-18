/**
 * @file      Graph.hpp
 * @author    Kaiky França dos Reis Silva
 * @brief     Defines the "Grafo" header
 * @version   0.1
 * @date      2026-06-15
 * @copyright Copyright (c) 2026 Kaiky França dos Reis Silva
 */

#ifndef GRAPH_ADJLIST_HPP
#define GRAPH_ADJLIST_HPP

#include <vector>
#include <list>

    class Graph_adjList {
        private:
            unsigned int number_of_vertex;
            std::vector<std::list<int> > adjList; //Graph structure
            int ** adjMatrix;

            void DFS(unsigned int startVertex, std::vector<bool>& visited); // Depth First Search
 
            void BFS(); //Breadth First Search

        public:
            //Constructor
            Graph_adjList(unsigned int number_of_vertex);
            
            Graph_adjList clone();

            ~Graph_adjList();

            //Add and Remove methods
            void addEdge(unsigned int origin, unsigned int destination);
            void removeEdge(unsigned int origin, unsigned int destination);

            //Transitive reduction method. The goal is to remove the reduntant edges
            void execute_transitive_reduction();

            void printGraph();
            
    };

#endif