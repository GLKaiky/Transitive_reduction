/**
 * @file      Graph_adjList.cpp
 * @authors   Kaiky França dos Reis Silva and Samuel Horta de Faria
 * @brief     Implementation of Graph operations and Transitive Reduction using an adjacency list representation.
 * @version   0.2
 * @date      2026-06-26
 * @copyright Copyright (c) 2026 Kaiky França dos Reis Silva
 */

#include "Graph_adjList.hpp"
#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

Graph_adjList::Graph_adjList(unsigned int number_of_vertex) {
    //Sets the number of vertices and resizes the main vector of lists
    this->number_of_vertex = number_of_vertex;
    this->adjList.resize(number_of_vertex);    
}

Graph_adjList::~Graph_adjList() { }

Graph_adjList Graph_adjList::clone() {

    //Instantiates a new graph and directly copies the list data structure
    Graph_adjList copiedGraph(this->number_of_vertex);
    copiedGraph.adjList = this->adjList;
    return copiedGraph;
}

void Graph_adjList::addEdge(unsigned int origin, unsigned int destination) {
    
    //Appends the destination vertex to the adjacency list of the origin vertex
    this->adjList[origin].push_back(destination); 
}

void Graph_adjList::removeEdge(unsigned int origin, unsigned int destination) {

    //Removes the specific destination vertex from the origin's list
    this->adjList[origin].remove(destination); 
}

void Graph_adjList::DFS(unsigned int startVertex, std::vector<bool>& visited) {
    std::stack<int> dfsStack;
    dfsStack.push(startVertex);
    
    while(!dfsStack.empty()) {
        int current_vertex = dfsStack.top();
        dfsStack.pop();

        //If the popped vertex hasn't been visited yet...
        if(!visited[current_vertex]){
            visited[current_vertex] = true;

            //Push all unvisited neighbors to the stack
            for(int neighbor : this->adjList[current_vertex]) {
                if(!visited[neighbor]) {
                    dfsStack.push(neighbor);    
                }
            }
        }
    }
}

void Graph_adjList::tarjanDFS(unsigned int u, unsigned int& timer, std::vector<int>& ids, 
                              std::vector<int>& low, std::vector<bool>& on_stack, 
                              std::stack<int>& s, std::vector<int>& scc_ids, int& scc_counter) {

    //Defines discovery time and lowest reachable time
    ids[u] = low[u] = timer++;
    s.push(u);
    on_stack[u] = true;

    //Visits all adjacent vertices
    for (int v : this->adjList[u]) {
        //If not visited, recurse and update low value
        if (ids[v] == -1) {
            tarjanDFS(v, timer, ids, low, on_stack, s, scc_ids, scc_counter);
            low[u] = std::min(low[u], low[v]);
        } 
        //Cross-edge or back-edge check
        else if (on_stack[v]) {
            low[u] = std::min(low[u], ids[v]);
        }
    }

    //SCC root is identified
    if (ids[u] == low[u]) {
        while (true) {
            int node = s.top();
            s.pop();
            on_stack[node] = false;
            scc_ids[node] = scc_counter; // Assign component ID
            if (node == static_cast<int>(u)) break;
        }
        scc_counter++;
    }
}

std::pair<std::vector<int>, int> Graph_adjList::findSCCs() {

    //Initialization of Tarjan's required tracking vectors.
    std::vector<int> ids(this->number_of_vertex, -1);       
    std::vector<int> low(this->number_of_vertex, 0);
    std::vector<bool> on_stack(this->number_of_vertex, false);
    std::stack<int> s;
    std::vector<int> scc_ids(this->number_of_vertex, -1);
    
    unsigned int timer = 0;
    int scc_counter = 0; 

    //Ensures disconnected components are also processed
    for (unsigned int i = 0; i < this->number_of_vertex; i++) {
        if (ids[i] == -1) {
            tarjanDFS(i, timer, ids, low, on_stack, s, scc_ids, scc_counter);
        }
    }
    return {scc_ids, scc_counter}; 
}

void Graph_adjList::execute_transitive_reduction() {

    //Phase 1: Find the cycles
    std::pair<std::vector<int>, int> tarjan_result = this->findSCCs();
    std::vector<int> scc_ids = tarjan_result.first;
    unsigned int num_sccs = tarjan_result.second;

    //Phase 2: Create a DAG connecting the condensed SCCs
    Graph_adjList DAG(num_sccs);
    for (unsigned int u = 0; u < this->number_of_vertex; u++) {
        for (int v : this->adjList[u]) {
            if (scc_ids[u] != scc_ids[v]) {
                bool exists = false;
                for (int neighbor : DAG.adjList[scc_ids[u]]) {
                    if (neighbor == scc_ids[v]) { exists = true; break; }
                }
                if (!exists) {
                    DAG.addEdge(scc_ids[u], scc_ids[v]);
                }
            }
        }
    }

    //Phase 3: Remove redundant edges using DFS to check reachability
    Graph_adjList DAG_snapshot = DAG.clone();
    for (unsigned int i = 0; i < DAG_snapshot.number_of_vertex; i++) {
        for (int neighbor : DAG_snapshot.adjList[i]) {
            
            //Temporarily remove the direct edge
            DAG.removeEdge(i, neighbor); 

            //Perform DFS to check if an alternative path still exists
            std::vector<bool> visited(DAG.number_of_vertex, false);
            DAG.DFS(i, visited); 
            
            //If the neighbor cannot be reached without the direct edge, put it back
            if (!visited[neighbor]) {
                DAG.addEdge(i, neighbor);
            }
        }
    }

    //Clear the original graph completely to reconstruct it
    for (unsigned int i = 0; i < this->number_of_vertex; i++) {
        this->adjList[i].clear();
    }

    //Group the vertices by their SCC
    std::vector<std::vector<int>> scc_groups(num_sccs);
    for (unsigned int i = 0; i < this->number_of_vertex; i++) {
        scc_groups[scc_ids[i]].push_back(i);
    }

    //Phase 4.1: Recreate simple cyclic paths for components with multiple vertices
    for (unsigned int k = 0; k < num_sccs; k++) {
        if (scc_groups[k].size() > 1) {
            for (size_t i = 0; i < scc_groups[k].size(); i++) {
                int u = scc_groups[k][i];

                //Forms a continuous loop returning to the first element
                int v = scc_groups[k][(i + 1) % scc_groups[k].size()]; 
                this->addEdge(u, v);
            }
        }
    }

    //Phase 4.2: Reconnect the bridges that survived the pruning
    for (unsigned int u = 0; u < num_sccs; u++) {
        for (int v : DAG.adjList[u]) {
            //Connects the lowest member of group "U" to the lowest member of group "V"
            int min_u = scc_groups[u][0];
            int min_v = scc_groups[v][0];
            this->addEdge(min_u, min_v);
        }
    }
}

void Graph_adjList::printGraph() {

    //Iterates through all lists printing the connections mapping visually
    for (unsigned int i = 0; i < this->number_of_vertex; i++) {
        std::cout << "|" << i << "| -> "; 
        for (int neighbor : this->adjList[i]) {
            std::cout << "|" << neighbor << "| ";   
        }
        std::cout << std::endl;
    }
}