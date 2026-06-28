# 1. Variáveis de Configuração
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g
TARGET = programa

# Variáveis de Diretório (Novidade aqui)
SRC_DIR = ./src
OBJ_DIR = ./obj

# 2. Arquivos do Projeto
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/lib/Graph_adjList.cpp $(SRC_DIR)/lib/Graph_adjMatrix.cpp $(SRC_DIR)/generator/gerador_de_grafo.cpp ${SRC_DIR}/benchmark/runner.cpp

# Mágica de substituição: troca o caminho do src/ pelo obj/ e a extensão .cpp por .o
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# 3. Regra Principal
all: $(TARGET)

# 4. Regra de Linkagem
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# 5. Regra de Compilação
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@) 
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 6. Regra de Limpeza
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET) $(FILE)