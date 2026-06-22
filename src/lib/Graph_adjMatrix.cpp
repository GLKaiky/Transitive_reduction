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

Graph_adjMatrix::Graph_adjMatrix(unsigned int number_of_vertices) {
    this->number_of_vertices = number_of_vertices; 
    this->adjMatrix = new bool*[number_of_vertices];

    int i = 0;
    for(i; i<number_of_vertices; i++){
        this->adjMatrix[i] = new bool[number_of_vertices]();
    }
}

Graph_adjMatrix::~Graph_adjMatrix() {
    int i = 0;
    for(i; i<this->number_of_vertices; i++) {
        delete[] this->adjMatrix[i];
    }
    delete[] this->adjMatrix;
}

Graph_adjMatrix Graph_adjMatrix::clone() {
    Graph_adjMatrix copiedGraph(this->number_of_vertices);
    for(unsigned int i = 0; i < this->number_of_vertices; i++) {
            for(unsigned int j = 0; j < this->number_of_vertices; j++) {
                copiedGraph.adjMatrix[i][j] = this->adjMatrix[i][j];
            }
        }

    return copiedGraph;
}

void Graph_adjMatrix::addEdge(unsigned int origin, unsigned int destination) {
    this->adjMatrix[origin][destination] = true;
}

void Graph_adjMatrix::removeEdge(unsigned int origin, unsigned int destination) {
    this->adjMatrix[origin][destination] = false;
}

void Graph_adjMatrix::floyd_warshall() {
    unsigned int k = 0;

    for(k; k<this->number_of_vertices; k++) {

        for(unsigned int i = 0; i < this->number_of_vertices; i++) {

            for(unsigned int j = 0; j< this->number_of_vertices; j++) {

                this->adjMatrix[i][j] = this->adjMatrix[i][j] || (this->adjMatrix[i][k] && this->adjMatrix[k][j]);
            }
        }
    }
}

