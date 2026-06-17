#include "./lib/Graph.hpp"
#include <iostream>

int main() {
    Graph g(3);

    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);

    std::cout << "Grafo original" << std::endl;

    g.printGraph();

    std::cout << "Com redução transitiva" << std::endl;
    
    g.execute_transitive_reduction();

    g.printGraph();
}