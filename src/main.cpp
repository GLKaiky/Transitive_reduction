/**
 * @file      main.cpp
 * @authors   Kaiky França dos Reis Silva and Samuel Horta de Faria
 * @brief     Main entry point of the program. Loads a graph from a file, executes Transitive Reduction, and prints the results.
 * @version   0.1
 * @date      2026-06-27
 * @copyright Copyright (c) 2026 Kaiky França dos Reis Silva
 */


#include "./lib/Graph_adjList.hpp"
#include "./lib/Graph_adjMatrix.hpp"
#include "./generator/gerador_de_grafo.hpp"
#include <iostream>

/***
 * @brief Main function that coordinates the graph loading and algorithm execution.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Returns 0 upon successful execution, or 1 if an error occurs.
 */
int main(int argc, char ** argv) {

    //Checks if the user provided the input file path as a command-line argument
    if(argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo.txt>\n";
        return 1;
    }

    //Pointers to hold the graph representations
    Graph_adjList* OriginalProposal = nullptr;
    Graph_adjMatrix * AhoProposal = nullptr;

    //Attempts to generate the graphs from the provided text file
    if(!gerar_Grafos(argv[1], AhoProposal, OriginalProposal)) {
        std::cerr << "Não foi possivel carregar o arquivo, ou ele ainda não está preenchido, está localizado na pasta inputs " << argv[1] << "\n";
        return 1;
    }

    std::cout << "\n\n";

    //Prints the original Adjacency List graph
    std::cout << "Lista de Adjacência:\n";
        OriginalProposal->printGraph();

        std::cout << "\n\n";

        //Prints the original Adjacency Matrix graph
        std::cout << "Matriz ORIGINAL:\n";
        AhoProposal->print();

        std::cout << "\n\n";

        //Executes the Transitive Reduction algorithm on both structures
        OriginalProposal->execute_transitive_reduction();
        AhoProposal->transitiveReduction();

        //Prints the reduced Adjacency List graph
        std::cout << "Lista de Adjacência REDUZIDA (Transitive Reduction):\n";
        OriginalProposal->printGraph();

        std::cout << "\n\n";

        //Prints the reduced Adjacency Matrix graph
        std::cout << "Matriz REDUZIDA:\n";
        AhoProposal->print();

        //Frees the dynamically allocated memory to prevent memory leaks
        delete OriginalProposal;
        delete AhoProposal;

        return 0;
}