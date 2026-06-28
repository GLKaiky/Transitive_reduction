# Trabalho Prático — Redução Transitiva em Grafos

## Disciplina: Projeto e Análise de Algoritmos (PAA)

## Professor: Silvio Jamil

### Pontifícia Universidade Católica de Minas Gerais (PUC Minas)

---

## 🎯 Objetivo do Trabalho

O objetivo deste Trabalho Prático (TP) é implementar, analisar e documentar um algoritmo de **Redução Transitiva em Grafos** puramente baseado em **caminhamento** (Busca em Profundidade — DFS).

A redução transitiva consiste em transformar um grafo original $G=(V,E)$ em um grafo reduzido $G^{\prime}=(V,E^{\prime})$ que mantém exatamente a mesma relação de atingibilidade entre qualquer par de vértices, mas elimina caminhos (arestas) redundantes.

**Restrição Principal:** O grafo resultante deve ser obrigatoriamente um **Subgrafo Estrito** do original. Ou seja, o algoritmo deve apenas identificar e *remover* arestas redundantes existentes através da navegação, sendo proibida a sintetização de arestas artificiais para a formação de anéis.

O projeto avalia aspectos críticos de:

* **Eficiência algorítmica** através de medições empíricas de tempo de execução.
* **Estruturas de representação:** O impacto de performance entre a utilização de Listas de Adjacência vs. Matrizes de Adjacência em cenários de grafos densos e esparsos.
* **Análise teórica:** Comportamento do algoritmo em cenários com ciclos (Componentes Fortemente Conexas) e grafos não-direcionados.

---

## 👥 Integrantes do Grupo
* [Kaiky França dos Reis Silva](https://kaikyfrs.com.br) 
* [Luís Fernando Rodrigues Braga](https://github.com/Trinalsolid) 
* [Davi Cândido de Almeida](https://github.com/DaviKandido) 
* [Victor Monteiro Martinelli Grataroli](https://github.com/Lonely-Warlock) 
* [Samuel Horta de Faria](https://github.com/SamuelHortadeFaria) 
* [Integrante 6](https://linkedin.com/in/seu-perfil) 
* [Integrante 7](https://github.com/seu-usuario) 

---

## 📂 Estrutura do Projeto

A organização de diretórios separa a lógica de negócios, a infraestrutura de compilação híbrida e a documentação científica (Artigo JBCS):

```text
TP_PAA/
│
├── documents/               # Relatório acadêmico seguindo as diretrizes da SBC/JBCS
│   ├── main.tex             # Arquivo-fonte principal em LaTeX (Obrigatório)
│   └── referencias.bib      # Base de dados bibliográficos
│
├── src/                     # Código-fonte principal escrito em C++
│   ├── lib/                 # Biblioteca core de estruturas de dados do projeto
│   │   ├── Graph_adjList.hpp / .cpp   # Implementação via Lista de Adjacência
│   │   ├── Graph_adjMatrix.hpp / .cpp # Implementação via Matriz de Adjacência
│   │   └── LeitorGrafo.hpp / .cpp     # Módulo utilitário para leitura de arquivos .txt
│   │
│   ├── generator/           # Gerador de grafos de teste (Sintéticos/DAGs/Aleatórios)
│   │   └── gerador_de_grafo.hpp / .cpp
│   │
│   └── main.cpp             # Ponto de entrada do programa (Instanciação e execução)
│
├── inputs/                  # Instâncias de teste (ex: sparse_graph.txt, dense_graph.txt)
├── CMakeLists.txt           # Configuração de compilação multiplataforma (Windows/Linux)
├── Makefile                 # Script de automação de compilação rápida (Linux/MacOS)
└── README.md                # Instruções gerais de configuração e execução

```

---

## 🚀 Como Compilar e Executar

O projeto possui suporte nativo para compilação em ambientes **Linux** (via `make`) e **Windows** (via `CMake` com MSVC ou MinGW), garantindo compatibilidade para toda a equipe. O compilador deve suportar o padrão **C++17**.

### Opção A: Ambiente Linux (Usando Makefile)

No diretório raiz do projeto, você pode compilar e já executar o programa passando o arquivo de teste desejado em um único comando:

```bash
# Compila e roda utilizando o grafo esparso de teste
make run FILE="inputs/sparse_graph.txt"

```

### Opção B: Ambiente Windows / VS Code (Usando CMake)

Para construir o projeto isolando os arquivos binários em uma pasta `build`:

```powershell
# 1. Crie o diretório de build e entre nele
mkdir build
cd build

# 2. Configure o projeto com o CMake
cmake ..

# 3. Compile o executável
cmake --build .

# 4. Execute passando o arquivo de entrada
.\Debug\programa.exe ..\inputs\sparse_graph.txt

```

*(No Linux usando CMake, o executável finaliza na raiz da pasta build como `./programa`).*

---

## 📊 Formato de Entrada (Arquivos `.txt`)

O programa utiliza a biblioteca `<fstream>` para carregar os grafos dinamicamente na memória. Os arquivos de entrada em `inputs/` devem seguir o formato padrão:

* A primeira linha deve conter um inteiro indicando a quantidade de vértices $V$.
* As linhas subsequentes devem conter pares de inteiros representando as arestas direcionadas (Origem $\rightarrow$ Destino).

**Exemplo:**

```text
3
0 1
1 2
2 0

```

---

## 🔬 Resultados e Relatório Teórico

As análises empíricas do tempo de execução e a justificativa da escolha das estruturas de dados estão documentadas detalhadamente no relatório final (`documents/main.pdf`).

O foco da análise recai sobre o contraste de performance:

* **Grafos Esparsos:** Vantagem de acesso temporal do DFS caminhando pela *Lista de Adjacência*.
* **Grafos Densos:** Vantagem de acesso direto $O(1)$ na validação e deleção de arestas redundantes utilizando a *Matriz de Adjacência*.