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

class Graph_adjMatrix {
    private:
        unsigned int number_of_vertrex;
        bool ** adjMatrix;
    
    public:

        Graph_adjMatrix(unsigned int number_of_vertex);

        void addEdge(unsigned int origin, unsigned int destination);
        
        void removeEdge(unsigned int origin, unsigned int destination);

        void warshall();
        
        ~Graph_adjMatrix();
        
        void printGraph();

        Graph_adjMatrix clone();


};

#endif