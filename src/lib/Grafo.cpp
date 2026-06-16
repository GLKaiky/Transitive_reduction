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


Graph::Graph(unsigned int number_of_vertex) {
    this->number_of_vertex = number_of_vertex;
    this->adjList.resize(number_of_vertex);
}


//Directec Edge
void Graph::addEdge(unsigned int origin, unsigned int destination) {
    this->adjList[origin].push_back(destination); //Point the origin vertex, to destination vertex A -> B -> C...
}

void Graph::removeEdge(unsigned int origin, unsigned int destination) {
    this->adjList[origin].remove(destination); //Remove the edges between vertices
}

void Graph::DFS(unsigned int startVertex) {
    std::stack<int> dfsStack;
    std::vector<bool> visited(this->number_of_vertex, false);
    
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




