#include "../lib/Graph_adjList.hpp"
#include "../lib/Graph_adjMatrix.hpp"
#include "../generator/gerador_de_grafo.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

#include "runner.hpp"

using namespace std;
using namespace std::chrono;

void runBenchmarkMatriz(const string& filepath, int vertices, int expected_edges, const string& tipo, ofstream& csvFile) {
    cout << "Testando MATRIZ: " << filepath << " | V: " << vertices << " | E: " << expected_edges << "..." << flush;

    Graph_adjList* OriginalProposal = nullptr; // Vai ser alocado, mas ignorado no teste
    Graph_adjMatrix* AhoProposal = nullptr;

    if (!gerar_Grafos(filepath.c_str(), AhoProposal, OriginalProposal)) {
        cerr << "\n[ERRO] Falha ao ler arquivo: " << filepath << "\n";
        return;
    }

    if (AhoProposal == nullptr) return;

    auto start = high_resolution_clock::now();
    AhoProposal->transitiveReduction();
    auto end = high_resolution_clock::now();
    
    auto tempo = duration_cast<microseconds>(end - start).count();

    csvFile << filepath << "," << vertices << "," << expected_edges << "," << tipo << ",Matriz," << tempo << "\n";

    delete OriginalProposal;
    delete AhoProposal;

    cout << " OK! (" << tempo << "us)\n";
}

void runBenchmarkLista(const string& filepath, int vertices, int expected_edges, const string& tipo, ofstream& csvFile) {
    cout << "Testando LISTA:  " << filepath << " | V: " << vertices << " | E: " << expected_edges << "..." << flush;

    Graph_adjList* OriginalProposal = nullptr;
    Graph_adjMatrix* AhoProposal = nullptr; // Vai ser alocado, mas ignorado no teste

    if (!gerar_Grafos(filepath.c_str(), AhoProposal, OriginalProposal)) {
        cerr << "\n[ERRO] Falha ao ler arquivo: " << filepath << "\n";
        return;
    }

    if (OriginalProposal == nullptr) return;

    auto start = high_resolution_clock::now();
    OriginalProposal->execute_transitive_reduction();
    auto end = high_resolution_clock::now();
    
    auto tempo = duration_cast<microseconds>(end - start).count();

    csvFile << filepath << "," << vertices << "," << expected_edges << "," << tipo << ",Lista," << tempo << "\n";

    delete OriginalProposal;
    delete AhoProposal;

    cout << " OK! (" << tempo << "us)\n";
}

