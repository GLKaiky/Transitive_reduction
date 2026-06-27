/**
 * @file      Graph_adjMatrix.hpp
 * @authors   Kaiky França dos Reis Silva and Samuel Horta de Faria
 * @brief     Declaration of the Graph class using an adjacency matrix representation.
 * @version   0.1
 * @date      2026-06-18
 * @copyright Copyright (c) 2026 Kaiky França dos Reis Silva
 */


#ifndef GRAPH_ADJMATRIX_HPP
#define GRAPH_ADJMATRIX_HPP

#include <vector>
#include <stack>
#include <utility>
class Graph_adjMatrix {
    private:
        unsigned int number_of_vertices;
        bool ** adjMatrix;

        /**
         * @brief             Auxiliary function for Tarjan's algorithm to find Strongly Connected Components (SCC) using DFS.
         * @param u           The current vertex being visited.
         * @param timer       Reference to the discovery timer.
         * @param ids         Vector storing the discovery times of visited vertices.
         * @param low         Vector storing the lowest discovery time reachable from the current vertex.
         * @param on_stack    Boolean vector indicating if a vertex is currently in the recursion stack.
         * @param s           The stack used to store the current SCC path.
         * @param scc_ids     Vector storing the ID of the SCC each vertex belongs to.
         * @param scc_counter Reference to the counter of discovered SCCs.
         */
        void tarjanDFS(unsigned int u, 
                   unsigned int& timer, 
                   std::vector<int>& ids, 
                   std::vector<int>& low, 
                   std::vector<bool>& on_stack, 
                   std::stack<int>& s, 
                   std::vector<int>& scc_ids, 
                   int& scc_counter);
    
    public:

        /**
         * @brief                    Constructor for the Graph_adjMatrix class
         * @param number_of_vertices The total number of vertices the graph will have.
         */
        Graph_adjMatrix(unsigned int number_of_vertices);
        
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
         * @brief Executes Warshall's algorithm to compute the transitive closure of the graph.
         */
        void Warshall();
        
        /**
         * @brief Destructor for the Graph_adjMatrix class. Frees the allocated memory.
         */
        ~Graph_adjMatrix();

        /**
         * @brief  Creates a Directed Acyclic Graph (DAG) by condensing Strongly Connected Components
         * @return Graph_adjMatrix Returns a new graph representing the DAG.
         */
        Graph_adjMatrix create_DAG();

        /**
         * @brief Performs the Transitive Reduction algorithm on the current graph.
         */
        void transitiveReduction();

        /**
         * @brief  Creates a copy of the current graph.
         * @return Graph_adjMatrix returns the copied graph.
         */
        Graph_adjMatrix clone();

        /**
         * @brief  Finds the Strongly Connected Components (SCCs) of the graph using Tarjan's algorithm.
         * @return Returns a pair containing the vector of SCC IDs for each vertex and the total number of SCCs.
         */
        std::pair<std::vector<int>, int> findSCCs();
        
        /**
         * @brief Prints the adjacency matrix.
         */
        void print();

};

#endif