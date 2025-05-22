# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall

# Nome do binário e fontes
TARGET = pagerank
SRC = pagerank.cpp

# Regra padrão
all: $(TARGET)

# Como compilar
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Limpa os binários
clean:
	rm -f $(TARGET)
