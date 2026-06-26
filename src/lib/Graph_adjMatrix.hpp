/**
 * @file      Graph_adjMatrix.hpp
 * @author    Kaiky França dos Reis Silva
 * @brief     
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

        void tarjanDFS(unsigned int u, 
                   unsigned int& timer, 
                   std::vector<int>& ids, 
                   std::vector<int>& low, 
                   std::vector<bool>& on_stack, 
                   std::stack<int>& s, 
                   std::vector<int>& scc_ids, 
                   int& scc_counter);
    
    public:

        Graph_adjMatrix(unsigned int number_of_vertices);

        void addEdge(unsigned int origin, unsigned int destination);
        
        void removeEdge(unsigned int origin, unsigned int destination);

        void Warshall();
        
        ~Graph_adjMatrix();
        
        void printGraph();

        Graph_adjMatrix create_DAG();

        void transitiveReduction();

        Graph_adjMatrix clone();
        
        std::pair<std::vector<int>, int> findSCCs();

        void print();

};

#endif