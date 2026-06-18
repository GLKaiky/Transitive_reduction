# 1. Variáveis de Configuração
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -g
TARGET = programa

# 2. Arquivos do Projeto
SRCS = ./src/main.cpp ./src/lib/Graph_adjList.cpp ./src/lib/Graph_adjMatrix.cpp
OBJS = $(SRCS:.cpp=.o)

# 3. Regra Principal (O que roda quando você digita apenas 'make')
all: $(TARGET)

# 4. Regra de Linkagem (Junta os .o para criar o executável final)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# 5. Regra de Compilação (Transforma .cpp em arquivos objeto .o)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 6. Regra de Limpeza (Apaga os arquivos gerados)
clean:
	rm -f $(OBJS) $(TARGET)