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

void Graph_adjMatrix::Warshall() {
    unsigned int k = 0;

    for(k; k<this->number_of_vertices; k++) {

        for(unsigned int i = 0; i < this->number_of_vertices; i++) {

            for(unsigned int j = 0; j< this->number_of_vertices; j++) {

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
    
    ids[u] = low[u] = timer++;
    s.push(u);
    on_stack[u] = true;

    for (unsigned int v = 0; v < this->number_of_vertices; v++) {
        
        if (this->adjMatrix[u][v]) {
            
            if (ids[v] == -1) {
                tarjanDFS(v, timer, ids, low, on_stack, s, scc_ids, scc_counter);
                
                low[u] = std::min(low[u], low[v]);
            }
            else if (on_stack[v]) {
                low[u] = std::min(low[u], ids[v]);
            }
            
        }
    }

    if (ids[u] == low[u]) {
        while (true) {
            int node = s.top();
            s.pop();
            on_stack[node] = false;
            
            scc_ids[node] = scc_counter;
            
            if (node == u) break;
        }
        scc_counter++;
    }
}

std::pair<std::vector<int>, int> Graph_adjMatrix::findSCCs() {
    std::vector<int> ids(this->number_of_vertices, -1);       
    std::vector<int> low(this->number_of_vertices, 0);
    std::vector<bool> on_stack(this->number_of_vertices, false);
    std::stack<int> s;
    
    std::vector<int> scc_ids(this->number_of_vertices, -1);
    
    unsigned int timer = 0;
    int scc_counter = 0; 

    for (unsigned int i = 0; i < this->number_of_vertices; i++) {
        if (ids[i] == -1) {
            tarjanDFS(i, timer, ids, low, on_stack, s, scc_ids, scc_counter);
        }
    }

    return {scc_ids, scc_counter}; 
}

Graph_adjMatrix Graph_adjMatrix::create_DAG() {
    std::pair<std::vector<int>, int> tarjan_result = this->findSCCs();
    std::vector<int> scc_ids = tarjan_result.first; 
    int number_of_cicles = tarjan_result.second;          

    Graph_adjMatrix DAG(number_of_cicles);

    for (unsigned int u = 0; u < this->number_of_vertices; u++) {
        for (unsigned int v = 0; v < this->number_of_vertices; v++) {
            
            if (this->adjMatrix[u][v] == true) {
                
                if (scc_ids[u] != scc_ids[v]) {
                    
                    DAG.addEdge(scc_ids[u], scc_ids[v]);
                }
            }
        }
    }


    return DAG;

}

void Graph_adjMatrix::transitiveReduction() {
    // Passo 1 e 2: Obter o DAG (G1) e os IDs dos componentes conexos
    Graph_adjMatrix DAG_original = create_DAG();
    std::pair<std::vector<int>, int> tarjan_result = this->findSCCs();
    std::vector<int> scc_ids = tarjan_result.first;
    unsigned int num_sccs = tarjan_result.second;

    // Passo 3 e 4: Fazer uma cópia para calcular o fecho transitivo (G2 e M3)
    Graph_adjMatrix DAG_fecho = DAG_original.clone();
    DAG_fecho.Warshall(); // Calcula os caminhos alcançáveis

    // Passo 5: Subtrair as arestas redundantes (G1^t = G1 - G3)
    for (unsigned int u = 0; u < num_sccs; u++) {
        for (unsigned int v = 0; v < num_sccs; v++) {
            if (DAG_original.adjMatrix[u][v]) { // Se existe aresta direta no DAG original
                
                bool is_redundant = false;
                // Procura um caminho alternativo passando por um vértice intermediário 'w'
                for (unsigned int w = 0; w < num_sccs; w++) {
                    if (w != u && w != v && DAG_original.adjMatrix[u][w] && DAG_fecho.adjMatrix[w][v]) {
                        is_redundant = true;
                        break;
                    }
                }
                
                // Se achou caminho alternativo, a aresta direta é redundante e deve ser removida
                if (is_redundant) {
                    DAG_original.adjMatrix[u][v] = false;
                }
            }
        }
    }

    // Passo 6: Expansão Cíclica Canônica
    // Cria uma nova matriz de adjacência limpa com o tamanho original do grafo
    bool** newMatrix = new bool*[this->number_of_vertices];
    for (unsigned int i = 0; i < this->number_of_vertices; i++) {
        newMatrix[i] = new bool[this->number_of_vertices](); // Inicializa tudo com false
    }

    // Agrupa os vértices originais por SCC (eles já entrarão ordenados pelo índice 0 a N)
    std::vector<std::vector<int>> scc_groups(num_sccs);
    for (unsigned int i = 0; i < this->number_of_vertices; i++) {
        scc_groups[scc_ids[i]].push_back(i);
    }

    // 6.1: Recriar os ciclos simples para SCCs com mais de 1 vértice
    for (unsigned int k = 0; k < num_sccs; k++) {
        if (scc_groups[k].size() > 1) {
            for (size_t i = 0; i < scc_groups[k].size(); i++) {
                int u = scc_groups[k][i];
                int v = scc_groups[k][(i + 1) % scc_groups[k].size()]; // O último liga de volta no primeiro
                newMatrix[u][v] = true;
            }
        }
    }

    // 6.2: Reconectar as pontes do DAG reduzido no grafo original
    for (unsigned int u = 0; u < num_sccs; u++) {
        for (unsigned int v = 0; v < num_sccs; v++) {
            if (DAG_original.adjMatrix[u][v]) {
                // O artigo pede para ligar o membro de menor índice da classe de origem ao de destino
                int min_u = scc_groups[u][0]; 
                int min_v = scc_groups[v][0];
                newMatrix[min_u][min_v] = true;
            }
        }
    }

    // Passo Final: Atualizar o objeto atual com a nova matriz reduzida
    for (unsigned int i = 0; i < this->number_of_vertices; i++) {
        delete[] this->adjMatrix[i]; // Limpa a memória da matriz velha
    }
    delete[] this->adjMatrix;

    this->adjMatrix = newMatrix; // Aponta para a nova matriz gerada
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