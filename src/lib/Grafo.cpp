/**
 * @file      Grafo.cpp
 * @author    Kaiky França dos Reis Silva
 * @brief     Defines 
 * @version   0.1
 * @date      2026-06-15
 * @copyright Copyright (c) 2026 Kaiky França dos Reis Silva
 */

#include "Graph.hpp"
#include <iostream>
#include <stack>
#include <vector>

/***
 * @brief A modified DFS, with bool vector "visited" is referenced in parameters
 */
void Graph::DFS(unsigned int startVertex, std::vector<bool>& visited ) {
    std::stack<int> dfsStack; //start the stack
    
    dfsStack.push(startVertex);
    while(!dfsStack.empty()) {

        int current_vertex = dfsStack.top();
        
        dfsStack.pop();

        if(!visited[current_vertex]){
            visited [current_vertex] = true;

            for(int neighbor : this->adjList[current_vertex]) {
                if(!visited[neighbor]) {
                    dfsStack.push(neighbor);    
                }
            }
        }
    }
}



Graph::Graph(unsigned int number_of_vertex) {
    this->number_of_vertex = number_of_vertex;
    this->adjList.resize(number_of_vertex);
}

Graph Graph::clone() {
    Graph copiedGraph(this->number_of_vertex);

    copiedGraph.adjList = this->adjList;

    return copiedGraph;
}

Graph::~Graph(){ }

//Directec Edge
void Graph::addEdge(unsigned int origin, unsigned int destination) {
    this->adjList[origin].push_back(destination); //Point the origin vertex, to destination vertex A -> B -> C...
}

void Graph::removeEdge(unsigned int origin, unsigned int destination) {
    this->adjList[origin].remove(destination); //Remove the edges between vertices
}

void Graph::execute_transitive_reduction() {
    unsigned int i = 0;
    Graph snapshot = this->clone();

    for(i; i < snapshot.number_of_vertex; i++) {

        for(int neighbor : snapshot.adjList[i]) {
            this->removeEdge(i, neighbor);

            std::vector<bool> existentPath(this->number_of_vertex, false);

            this->DFS(i, existentPath);

            if(!existentPath[neighbor]) {
                this->addEdge(i, neighbor);
            }
        }
    }
}

void Graph::printGraph() {
    int i = 0;

    for(i; i< this->number_of_vertex; i++) {
        std::cout << "|" << i << "|" << " -> "; 
        for(int neighbor : this->adjList[i]){
            std::cout << "|" << neighbor << "| ";   
        }

        std::cout << std::endl;
    }
}