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
#include "./benchmark/runner.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>


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

   /* std::ofstream csvFile("resultados_benchmark.csv");
    
    if (!csvFile.is_open()) {
        std::cerr << "Erro fatal: Nao foi possivel criar o arquivo CSV!\n";
        return 1;
    }

    // O cabeçalho agora tem uma coluna dedicada para o Algoritmo
    csvFile << "arquivo,vertices,arestas,tipo_densidade,algoritmo,tempo_us\n";

    std::cout << "==========================================\n";
    std::cout << " INICIANDO BENCHMARK ISOLADO\n";
    std::cout << "==========================================\n\n";

    // ---------------------------------------------------------
    // BATERIA 1: SOMENTE A MATRIZ
    // ---------------------------------------------------------
    std::cout << ">>> INICIANDO BATERIA DA MATRIZ (Aho)\n";
    runBenchmarkMatriz("inputs/esparso_100.txt", 100, 250, "Esparso", csvFile);
    runBenchmarkMatriz("inputs/esparso_250.txt", 250, 600, "Esparso", csvFile);
    runBenchmarkMatriz("inputs/esparso_500.txt", 500, 1200, "Esparso", csvFile);
    runBenchmarkMatriz("inputs/esparso_1000.txt", 1000, 2500, "Esparso", csvFile);
    
    runBenchmarkMatriz("inputs/denso_100.txt", 100, 8000, "Denso", csvFile);
    runBenchmarkMatriz("inputs/denso_250.txt", 250, 55000, "Denso", csvFile);
    runBenchmarkMatriz("inputs/denso_500.txt", 500, 220000, "Denso", csvFile);

    std::cout << "\n------------------------------------------\n";

    // ---------------------------------------------------------
    // BATERIA 2: SOMENTE A LISTA
    // ---------------------------------------------------------
    std::cout << ">>> INICIANDO BATERIA DA LISTA (Original/DFS)\n";
    runBenchmarkLista("inputs/esparso_100.txt", 100, 250, "Esparso", csvFile);
    runBenchmarkLista("inputs/esparso_250.txt", 250, 600, "Esparso", csvFile);
    runBenchmarkLista("inputs/esparso_500.txt", 500, 1200, "Esparso", csvFile);
    runBenchmarkLista("inputs/esparso_1000.txt", 1000, 2500, "Esparso", csvFile);
    
    runBenchmarkLista("inputs/denso_100.txt", 100, 8000, "Denso", csvFile);
    runBenchmarkLista("inputs/denso_250.txt", 250, 55000, "Denso", csvFile);
    runBenchmarkLista("inputs/denso_500.txt", 500, 220000, "Denso", csvFile);

    csvFile.close();
    
    std::cout << "\n==========================================\n";
    std::cout << " Resultados gravados em 'resultados_benchmark.csv'\n";
    
    return 0;*/
}