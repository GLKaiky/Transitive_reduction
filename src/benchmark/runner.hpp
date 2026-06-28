#ifndef RUNNER_HPP
#define RUNNER_HPP

#include "../lib/Graph_adjList.hpp"
#include "../lib/Graph_adjMatrix.hpp"
#include "../generator/gerador_de_grafo.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

void runBenchmarkMatriz(const std::string& filepath, int vertices, int expected_edges, const std::string& tipo, std::ofstream& csvFile);

void runBenchmarkLista(const std::string& filepath, int vertices, int expected_edges, const std::string& tipo, std:: ofstream& csvFile);

#endif