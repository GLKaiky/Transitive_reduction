# Trabalho Prático — Redução Transitiva em Grafos
## Disciplina: Projeto e Análise de Algoritmos (PAA)
## Professor: Silvio Jamil
### Pontifícia Universidade Católica de Minas Gerais (PUC Minas)

---

## 🎯 Objetivo do Trabalho
O objetivo deste Trabalho Prático (TP) é implementar, analisar e documentar algoritmos de **Redução Transitiva em Grafos** baseado em **caminhamento** (como busca em profundidade — DFS ou busca em largura — BFS). 

A redução transitiva consiste em transformar um grafo original $G=(V,E)$ em um grafo reduzido $G^{\prime}=(V,E^{\prime})$ que mantém exatamente a mesma relação de atingibilidade entre qualquer par de vértices, mas elimina caminhos redundantes. Dessa forma, se existe um caminho entre dois vértices no grafo original, haverá apenas um único caminho direto ou indireto entre eles no grafo reduzido.

O projeto avalia aspectos críticos de:
* **Eficiência algorítmica** através de medições empíricas (benchmarks de tempo de CPU).
* **Estruturas de representação** de grafos (impacto de listas vs. matrizes de adjacência).
* **Análise teórica** da aplicação do algoritmo em cenários específicos, como grafos não-direcionados.

---

## 👥 Integrantes do Grupo
* [Kaiky França dos Reis Silva](https://kaikyfrs.com.br) 
* [Luís Fernando Rodrigues Braga](https://github.com/Trinalsolid) 
* [Integrante 3](https://github.com/seu-usuario) 
* [Integrante 4](https://linkedin.com/in/seu-perfil) 
* [Integrante 5](https://github.com/seu-usuario) 
* [Integrante 6](https://linkedin.com/in/seu-perfil) 
* [Integrante 7](https://github.com/seu-usuario) 

---

## 📂 Estrutura do Projeto

Abaixo está descrita a organização de diretórios adotada para garantir a modularidade da aplicação, separando a lógica de negócios, os experimentos e a documentação científica:

```text
TP_PAA/
│
├── documents/               # Relatório acadêmico seguindo as diretrizes da SBC/JBCS
│   ├── main.tex             # Arquivo-fonte principal em LaTeX (Obrigatório)
│   ├── referencias.bib      # Base de dados bibliográficos das referências citadas
│   └── figuras/             # Imagens e gráficos gerados para o relatório
│
├── src/                     # Código-fonte principal escrito em C++
│   ├── benchmark/           # Infraestrutura para testes de performance e análise de tempo
│   │   └── runner.cpp       # Módulo que automatiza execuções repetidas e extrai métricas (<chrono>)
│   │
│   ├── lib/                 # Biblioteca core de estruturas de dados do projeto
│   │   ├── grafo.hpp        # Declaração da classe Grafo (Matriz/Lista de Adjacência)
│   │   └── grafo.cpp        # Implementação dos métodos de manipulação do grafo
│   │
│   ├── algorithms/          # Implementação dos algoritmos centrais de análise
│   │   ├── reducao.hpp      # Protótipo do algoritmo de redução por caminhamento
│   │   └── reducao.cpp      # Implementação lógica da remoção de transitividade
│   │
│   ├── generator/           # Gerador de grafos de teste (Sintéticos/DAGs/Aleatórios)
│   │   ├── gerador_grafo.hpp
│   │   └── gerador_grafo.cpp
│   │
│   └── main.cpp             # Ponto de entrada do programa (Interface de Linha de Comando - CLI)
│
├── inputs/                  # Instâncias de teste geradas para alimentar o benchmark (.txt)
├── outputs/                 # Grafos reduzidos resultantes e planilhas de log exportadas (.csv)
├── Makefile                 # Script de automação do processo de compilação
└── README.md                # Instruções gerais de configuração e execução do ecossistema
```

---

## 🚀 Como Compilar e Executar

### Pré-requisitos
* Compilador GCC compatível com o padrão **C++17** ou superior.
* Ferramenta `make` para automação.

### Passos para Compilação
No diretório raiz do projeto, utilize o comando `make` para compilar todo o código automaticamente utilizando as regras otimizadas do arquivo `Makefile`:

```bash
make
```

### Execução do Programa Principal
O programa está preparado para receber argumentos via linha de comando para facilitar a execução de testes automatizados:

```bash
./tp_paa --input inputs/grafo_100_vertices.txt --output outputs/reduzido_100.txt
```

### Execução do Benchmark
Para rodar a bateria de testes automatizados e gerar os dados de performance:

```bash
./benchmark_runner
```

---

## 📊 Resultados e Experimentos

Esta seção apresenta as análises empíricas do tempo de execução do algoritmo de redução transitiva conforme a variação do número de vértices $|V|$ e a densidade de arestas $|E|$ no grafo.

### Desempenho Temporal
O gráfico abaixo ilustra o comportamento do algoritmo baseado em caminhamento sob diferentes cenários de densidade (grafos esparsos vs. grafos densos):

![Gráfico de Resultados Experimentais](documents/figuras/grafico_tempo.png)

> **Nota de Análise:** Como pode ser observado no gráfico de desempenho, o impacto da estrutura escolhida em `src/lib/` dita o coeficiente de crescimento da curva à medida que a matriz ou lista é percorrida pelo caminhamento. Maiores detalhes sobre as curvas de complexidade assintótica empírica encontram-se documentados detalhadamente no relatório final em `documents/main.pdf`.
