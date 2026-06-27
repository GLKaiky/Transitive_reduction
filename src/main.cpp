/**
 * @file      main.cpp
 * @author    Kaiky França dos Reis Silva
 * @brief     
 * @version   0.1
 * @date      2026-06-27
 * @copyright Copyright (c) 2026 Kaiky França dos Reis Silva
 */


#include "./lib/Graph_adjList.hpp"
#include "./lib/Graph_adjMatrix.hpp"
#include "./generator/gerador_de_grafo.hpp"
#include <iostream>

int main(int argc, char ** argv) {

    if(argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo.txt>\n";
        return 1;
    }

    Graph_adjList* OriginalProposal = nullptr;


    Graph_adjMatrix * AhoProposal = nullptr;

    if(!gerar_Grafos(argv[1], AhoProposal, OriginalProposal)) {
        std::cerr << "Não foi possivel carregar o arquivo, ou ele ainda não está preenchido, está localizado na pasta inputs " << argv[1] << "\n";
        return 1;
    }


    std::cout << "\n\n";

    std::cout << "Lista de Adjacência:\n";
        OriginalProposal->printGraph();

        std::cout << "\n\n";

        std::cout << "Matriz ORIGINAL:\n";
        AhoProposal->print();


        std::cout << "\n\n";

        OriginalProposal->execute_transitive_reduction();
        AhoProposal->transitiveReduction();

        std::cout << "Lista de Adjacência REDUZIDA (Transitive Reduction):\n";
        OriginalProposal->printGraph();


        std::cout << "\n\n";

        std::cout << "Matriz REDUZIDA:\n";
        AhoProposal->print();

        delete OriginalProposal;
        delete AhoProposal;

        return 0;
}