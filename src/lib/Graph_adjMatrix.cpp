/**
 * @file      Graph_adjMatrix.cpp
 * @author    Kaiky França dos Reis Silva
 * @brief     
 * @version   0.1
 * @date      2026-06-18
 * @copyright Copyright (c) 2026 Kaiky França dos Reis Silva
 */


#include "Graph_adjMatrix.hpp"
#include <iostream>

Graph_adjMatrix::Graph_adjMatrix(unsigned int number_of_vertex) {
    this->number_of_vertrex = number_of_vertex; 
    this->adjMatrix = new bool*[number_of_vertex];

    int i = 0;
    for(i; i<number_of_vertex; i++){
        this->adjMatrix[i] = new bool[number_of_vertex]();
    }
}

Graph_adjMatrix::~Graph_adjMatrix() {
    int i = 0;
    for(i; i<this->number_of_vertrex; i++) {
        delete[] this->adjMatrix[i];
    }
    delete[] this->adjMatrix;
}

Graph_adjMatrix Graph_adjMatrix::clone() {
    Graph_adjMatrix copiedGraph(this->number_of_vertrex);
    copiedGraph.adjMatrix = this->adjMatrix;

    return copiedGraph;
}

void Graph_adjMatrix::addEdge(unsigned int origin, unsigned int destination) {
    this->adjMatrix[origin][destination] = true;
}

void Graph_adjMatrix::removeEdge(unsigned int origin, unsigned int destination) {
    this->adjMatrix[origin][destination] = false;
}

void Graph_adjMatrix::warshall() {
    
}