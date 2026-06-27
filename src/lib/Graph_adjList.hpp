/**
 * @file      Graph_adjList.hpp
 * @authors   Kaiky França dos Reis Silva and Samuel Horta de Faria
 * @brief     Declaration of the Graph class using an adjacency list representation.
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

        /**
         * @brief             Performs a Depth First Search (DFS) starting from a specific vertex.
         * @param startVertex The vertex from which the search begins.
         * @param visited     A boolean vector tracking visited vertices to avoid cycles.
         */
        void DFS(unsigned int startVertex, std::vector<bool>& visited); 
        
        /**
         * @brief             Helper function for Tarjan's algorithm to find Strongly Connected Components.
         * @param u           The current vertex being visited.
         * @param timer       References to the discovery timer.
         * @param ids         Vector storing discovery times.
         * @param low         Vector storing the lowest reachable discovery time.
         * @param on_stack    Boolean vector indicating if a vertex is in the recursion stack.
         * @param s           The stack holding the current path.
         * @param scc_ids     Vector storing the ID of the SCC each vertex belongs to.
         * @param scc_counter References to the total number of SCCs found.
         */
        void tarjanDFS(unsigned int u, unsigned int& timer, std::vector<int>& ids, 
                       std::vector<int>& low, std::vector<bool>& on_stack, 
                       std::stack<int>& s, std::vector<int>& scc_ids, int& scc_counter);
        
        /**
         * @brief  Finds the Strongly Connected Components (SCCs) using Tarjan's algorithm.
         * @return Returns SCC IDs mapped to vertices and total SCC count.
         */
        std::pair<std::vector<int>, int> findSCCs();

    public:
        /**
         * @brief                  Constructor for the Graph_adjList class.
         * @param number_of_vertex The total number of vertices the graph will have.
         */
        Graph_adjList(unsigned int number_of_vertex);
        
        /**
         * @brief  Creates a copy of the current graph.
         * @return Returns the copied graph.
         */
        Graph_adjList clone();
        
        /**
         * @brief Destructor for the Graph_adjList class.
         */
        ~Graph_adjList();

        /**
         * @brief             Adds a directed edge between two vertices.
         * @param origin      The starting vertex of the edge.
         * @param destination The ending vertex of the edge.
         */
        void addEdge(unsigned int origin, unsigned int destination);

        /**
         * @brief             Removes a directed edge between two vertices.
         * @param origin      The starting vertex of the edge.
         * @param destination The ending vertex of the edge.
         */
        void removeEdge(unsigned int origin, unsigned int destination);

        /**
         * @brief Executes the Transitive Reduction algorithm on the adjacency list graph.
         */
        void execute_transitive_reduction();

        /**
         * @brief Prints the adjacency list.
         */
        void printGraph();
};

#endif