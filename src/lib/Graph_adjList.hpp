/**
 * @file      Graph_adjList.hpp
 * @author    Kaiky França dos Reis Silva
 * @brief     Defines the "Grafo" header
 * @version   0.2
 * @date      2026-06-26
 * @copyright Copyright (c) 2026 Kaiky França dos Reis Silva
 */

#ifndef GRAPH_ADJLIST_HPP
#define GRAPH_ADJLIST_HPP

#include <vector>
#include <list>
#include <stack>
#include <utility> 

class Graph_adjList {
    private:
        unsigned int number_of_vertex;
        std::vector<std::list<int>> adjList; 
        void DFS(unsigned int startVertex, std::vector<bool>& visited); 
        
        void tarjanDFS(unsigned int u, unsigned int& timer, std::vector<int>& ids, 
                       std::vector<int>& low, std::vector<bool>& on_stack, 
                       std::stack<int>& s, std::vector<int>& scc_ids, int& scc_counter);
                       
        std::pair<std::vector<int>, int> findSCCs();

    public:
        // Constructor
        Graph_adjList(unsigned int number_of_vertex);
        
        Graph_adjList clone();

        ~Graph_adjList();

        // Add and Remove methods
        void addEdge(unsigned int origin, unsigned int destination);
        void removeEdge(unsigned int origin, unsigned int destination);

        // Transitive reduction method
        void execute_transitive_reduction();

        void printGraph();
};

#endif