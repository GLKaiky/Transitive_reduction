/**
 * @file      Graph_adjMatrix.cpp
 * @authors   Kaiky França dos Reis Silva and Samuel Horta de Faria
 * @brief     Implementation of Graph operations and Transitive Reduction using an adjacency matrix representation.
 * @version   0.1
 * @date      2026-06-18
 * @copyright Copyright (c) 2026 Kaiky França dos Reis Silva
 */


#include "Graph_adjMatrix.hpp"
#include <iostream>

Graph_adjMatrix::Graph_adjMatrix(unsigned int number_of_vertices) {

    //Sets the number of vertices and allocates an array of boolean pointers
    this->number_of_vertices = number_of_vertices; 
    this->adjMatrix = new bool*[number_of_vertices];

    //Allocates each row and initializes with 0 (false)
    int i = 0;
    for(i; i<number_of_vertices; i++){
        this->adjMatrix[i] = new bool[number_of_vertices]();
    }
}

Graph_adjMatrix::~Graph_adjMatrix() {

    //Iterates through all rows and deletes them to prevent memory leaks.
    int i = 0;
    for(i; i<this->number_of_vertices; i++) {
        delete[] this->adjMatrix[i];
    }
    //Deletes main array of pointers
    delete[] this->adjMatrix;
}

Graph_adjMatrix Graph_adjMatrix::clone() {

    //Creates a new graph with the same number of vertices
    Graph_adjMatrix copiedGraph(this->number_of_vertices);

    //Iterates through the matrix and copies the boolean values
    for(unsigned int i = 0; i < this->number_of_vertices; i++) {
            for(unsigned int j = 0; j < this->number_of_vertices; j++) {
                copiedGraph.adjMatrix[i][j] = this->adjMatrix[i][j];
            }
        }

    return copiedGraph;
}

void Graph_adjMatrix::addEdge(unsigned int origin, unsigned int destination) {
    //Sets the matrix position to true, indicating an edge exists
    this->adjMatrix[origin][destination] = true;
}

void Graph_adjMatrix::removeEdge(unsigned int origin, unsigned int destination) {
    //Sets the matrix position to false, removing the edge
    this->adjMatrix[origin][destination] = false;
}

void Graph_adjMatrix::Warshall() {
    unsigned int k = 0;

    //"k" is the intermediate vertex being tested
    for(k; k<this->number_of_vertices; k++) {
        //"i" is the origin vertex
        for(unsigned int i = 0; i < this->number_of_vertices; i++) {
            //"j" is the destination vertex
            for(unsigned int j = 0; j< this->number_of_vertices; j++) {
                //If there is a path from "i" to "j", or a path from "i" to "k" and "k" to "j", set to true
                this->adjMatrix[i][j] = this->adjMatrix[i][j] || (this->adjMatrix[i][k] && this->adjMatrix[k][j]);
            }
        }
    }
}

void Graph_adjMatrix::tarjanDFS(unsigned int u, 
                               unsigned int& timer, 
                               std::vector<int>& ids, 
                               std::vector<int>& low, 
                               std::vector<bool>& on_stack, 
                               std::stack<int>& s, 
                               std::vector<int>& scc_ids, 
                               int& scc_counter) {
    
    //Initialize discovery time and low value
    ids[u] = low[u] = timer++;
    s.push(u);
    on_stack[u] = true;
    
    //Iterate through all possible destinations.
    for (unsigned int v = 0; v < this->number_of_vertices; v++) {
        
        //If exists an edge from "u" to "v"...
        if (this->adjMatrix[u][v]) {
            //If "v" is not visited, recurse
            if (ids[v] == -1) {
                tarjanDFS(v, timer, ids, low, on_stack, s, scc_ids, scc_counter);
                //Update low value of "u" based on the subtree
                low[u] = std::min(low[u], low[v]);
            }
            //If "v" is visited and on the stack, it's a back-edge
            else if (on_stack[v]) {
                low[u] = std::min(low[u], ids[v]);
            }
            
        }
    }

    //If "u" is a root node, pop the stack and generate an SCC
    if (ids[u] == low[u]) {
        while (true) {
            int node = s.top();
            s.pop();
            on_stack[node] = false;
            
            //Defines the current SCC ID to the popped node
            scc_ids[node] = scc_counter;
            
            if (node == u) break;
        }
        //Increments the SCC counter for the next component.
        scc_counter++;
    }
}

std::pair<std::vector<int>, int> Graph_adjMatrix::findSCCs() {

    //Initializes necessary vectors for Tarjan's algorithm
    std::vector<int> ids(this->number_of_vertices, -1);       
    std::vector<int> low(this->number_of_vertices, 0);
    std::vector<bool> on_stack(this->number_of_vertices, false);
    std::stack<int> s;
    
    std::vector<int> scc_ids(this->number_of_vertices, -1);
    
    unsigned int timer = 0;
    int scc_counter = 0; 

    //Run DFS for each unvisited vertex
    for (unsigned int i = 0; i < this->number_of_vertices; i++) {
        if (ids[i] == -1) {
            tarjanDFS(i, timer, ids, low, on_stack, s, scc_ids, scc_counter);
        }
    }

    return {scc_ids, scc_counter}; 
}

Graph_adjMatrix Graph_adjMatrix::create_DAG() {

    //Retrieves the SCC information
    std::pair<std::vector<int>, int> tarjan_result = this->findSCCs();
    std::vector<int> scc_ids = tarjan_result.first; 
    int number_of_cicles = tarjan_result.second;          

    //Creates a new graph with vertices equal to the number of SCCs
    Graph_adjMatrix DAG(number_of_cicles);

    //Maps original edges to the new condensed DAG
    for (unsigned int u = 0; u < this->number_of_vertices; u++) {
        for (unsigned int v = 0; v < this->number_of_vertices; v++) {
            
            if (this->adjMatrix[u][v] == true) {
                
                //If vertices belong to different SCCs, add an edge in the DAG
                if (scc_ids[u] != scc_ids[v]) {
                    
                    DAG.addEdge(scc_ids[u], scc_ids[v]);
                }
            }
        }
    }


    return DAG;
}

void Graph_adjMatrix::transitiveReduction() {

    //Step 1 and 2: Obtain the DAG (G1) and the IDs of the connected components
    Graph_adjMatrix DAG_original = create_DAG();
    std::pair<std::vector<int>, int> tarjan_result = this->findSCCs();
    std::vector<int> scc_ids = tarjan_result.first;
    unsigned int num_sccs = tarjan_result.second;

    //Step 3 and 4: Make a copy to calculate the transitive closure (G2 e M3)
    Graph_adjMatrix DAG_fecho = DAG_original.clone();
    DAG_fecho.Warshall(); // Calculates the reachable paths

    //Step 5: Subtract the redundant edges (G1^t = G1 - G3)
    for (unsigned int u = 0; u < num_sccs; u++) {
        for (unsigned int v = 0; v < num_sccs; v++) {

            //If there is a direct edge in the original DAG...
            if (DAG_original.adjMatrix[u][v]) {
                
                bool is_redundant = false;
                //Looks for an alternate path passing through a intermediate vertex "w"
                for (unsigned int w = 0; w < num_sccs; w++) {
                    if (w != u && w != v && DAG_original.adjMatrix[u][w] && DAG_fecho.adjMatrix[w][v]) {
                        is_redundant = true;
                        break;
                    }
                }
                
                //If found an alternative path, the direct edge is redudant and must be removed
                if (is_redundant) {
                    DAG_original.adjMatrix[u][v] = false;
                }
            }
        }
    }

    //Step 6: Canonical Cyclic Expansion
    //Creates a new clean adjacency matrix with the original size of the graph.
    bool** newMatrix = new bool*[this->number_of_vertices];
    for (unsigned int i = 0; i < this->number_of_vertices; i++) {

        //Initializes everything with false.
        newMatrix[i] = new bool[this->number_of_vertices]();
    }

    //Groups original vertices by SCC (they will naturally enter ordered by index 0 to N)
    std::vector<std::vector<int>> scc_groups(num_sccs);
    for (unsigned int i = 0; i < this->number_of_vertices; i++) {
        scc_groups[scc_ids[i]].push_back(i);
    }

    //Step 6.1: Recreate simple cycles for SSCs with more then 1 vertex
    for (unsigned int k = 0; k < num_sccs; k++) {
        if (scc_groups[k].size() > 1) {
            for (size_t i = 0; i < scc_groups[k].size(); i++) {
                int u = scc_groups[k][i];

                //The last one connects back to the first one
                int v = scc_groups[k][(i + 1) % scc_groups[k].size()];
                newMatrix[u][v] = true;
            }
        }
    }

    //Step 6.2: Reconnect the bridges from the reduced DAG into the original graph
    for (unsigned int u = 0; u < num_sccs; u++) {
        for (unsigned int v = 0; v < num_sccs; v++) {
            if (DAG_original.adjMatrix[u][v]) {

                //The paper requests connecting the lowest index member of the origin class to the destination class
                int min_u = scc_groups[u][0]; 
                int min_v = scc_groups[v][0];
                newMatrix[min_u][min_v] = true;
            }
        }
    }

    //Final Step: Update the current object with the new reduced matrix
    for (unsigned int i = 0; i < this->number_of_vertices; i++) {
        //Clears the memory of the old matrix
        delete[] this->adjMatrix[i];
    }
    delete[] this->adjMatrix;

    //Points to the new generated matrix
    this->adjMatrix = newMatrix;
}

void Graph_adjMatrix::print() {
    std::cout << "  ";
    for (unsigned int i = 0; i < number_of_vertices; i++) std::cout << i << " ";
    std::cout << "\n";
    for (unsigned int i = 0; i < number_of_vertices; i++) {
        std::cout << i << " ";
        for (unsigned int j = 0; j < number_of_vertices; j++) {
            std::cout << (adjMatrix[i][j] ? "1 " : "0 ");
        }
        std::cout << "\n";
    }
    std::cout << "-----------------\n";
}