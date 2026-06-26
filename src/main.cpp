#include "./lib/Graph_adjList.hpp"
#include "./lib/Graph_adjMatrix.hpp"
#include <iostream>

int main() {
    Graph_adjList gU(3);

    
    // Cria um grafo com 4 vértices
    Graph_adjMatrix g(3);

    // Adiciona o caminho principal e o ciclo
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 1);
    g.addEdge(1, 0); 

    gU.addEdge(0, 1);
    gU.addEdge(1, 2);
    gU.addEdge(2, 1);
    gU.addEdge(1, 0); 
    // Adiciona a aresta REDUNDANTE (0 direto para 2)

    std::cout << "Matriz ORIGINAL:\n";
    g.print();

    std::cout << "Matriz ORIGINAL ADJ:\n";
    gU.printGraph();

    // Roda a mágica
    g.transitiveReduction();

    gU.execute_transitive_reduction();

    std::cout << "Matriz REDUZIDA (Transitive Reduction):\n";
    g.print();

    std::cout << "Matriz REDUZIDA ADJ:\n";
    gU.printGraph();



    return 0;
}