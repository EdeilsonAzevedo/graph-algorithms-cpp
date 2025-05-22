# Graph Algorithms in C++

Uma coleção abrangente e otimizada de algoritmos clássicos e modernos sobre grafos, implementados em C++17 com foco em eficiência, modularidade e facilidade de uso.

## 📖 Sobre o Projeto

Este repositório oferece implementações robustas de algoritmos fundamentais da teoria dos grafos, cada um otimizado para casos de uso específicos e acompanhado de documentação detalhada, testes automatizados e exemplos práticos.

**Características principais:**
- 🚀 **Performance otimizada** com estruturas de dados eficientes
- 📚 **Documentação completa** com fundamentação matemática
- 🧪 **Testes automatizados** para validação e demonstração
- 🛠️ **Interface uniforme** via linha de comando
- 📦 **Build system** com Makefile padronizado

## 📚 Algoritmos Implementados

| Algoritmo | Problema | Complexidade | Estruturas Utilizadas | Aplicações |
|-----------|----------|--------------|----------------------|-------------|
| **Dijkstra** | Caminho mínimo (pesos ≥ 0) | O((V+E) log V) | Heap binário, Lista adjacência | GPS, roteamento, jogos |
| **Prim** | Árvore Geradora Mínima | O(E log V) | Fila de prioridade | Redes, clustering, circuitos |
| **Kruskal** | Árvore Geradora Mínima | O(E log E) | Union-Find otimizado | Telecomunicações, energia |
| **Kosaraju** | Componentes Fortemente Conexas | O(V + E) | DFS, Stack | Análise de dependências |
| **PageRank** | Centralidade em grafos direcionados | O(k(V + E)) | Sistema dinâmico iterativo | Motores de busca, redes sociais |

## 🏗️ Estrutura do Projeto

```
graph-algorithms-cpp/
├── Dijkstra/              # Algoritmo de Dijkstra (estrutura modular)
├── Prim/                  # Algoritmo de Prim (estrutura modular)
├── Kruskal/               # Algoritmo de Kruskal
│   ├── kruskal.cpp
│   ├── Makefile
│   └── README.md
├── Kosaraju/              # Componentes Fortemente Conexas
│   ├── kosaraju.cpp
│   ├── Makefile
│   └── README.md
├── pagerank/              # Algoritmo PageRank
│   ├── pagerank.cpp
│   ├── makefile
│   └── README.md
├── helps/                 # Arquivos de ajuda dos algoritmos
│   ├── kosaraju_help.txt
│   ├── kruskal_help.txt
│   └── pagerank_help.txt
├── tests/                 # Sistema de testes automatizados
│   ├── agm/              # Testes de Árvore Geradora Mínima
│   │   ├── inputs/       # Grafos de teste (.mtx)
│   │   ├── expected_costs.txt
│   │   └── test.sh
│   ├── pr/               # Testes do PageRank
│   │   ├── inputs/       # Grafos para PageRank (.dat)
│   │   └── test.sh
│   ├── scc/              # Testes de SCC (Kosaraju)
│   │   ├── inputs/       # Grafos de entrada (.dat)
│   │   ├── outputs/      # Saídas esperadas (.dat)
│   │   └── test.sh
│   └── bin/              # Binários para testes
└── README.md
```

## 🚀 Início Rápido

### Pré-requisitos

- **Compilador C++17** (GCC 7+, Clang 5+, ou equivalente)
- **Make** para automação de build
- **Sistema Unix-like** (Linux, macOS) para scripts de teste

### Instalação e Compilação

```bash
# Clone o repositório
git clone https://github.com/EdeilsonAzevedo/graph-algorithms-cpp.git
cd graph-algorithms-cpp

```

### Execução Básica

```bash
# Visualizar opções disponíveis
./pagerank -h
./kruskal -h
./dijkstra -h

# Exemplo de uso do PageRank
./pagerank -f examples/web_graph.txt -k 5 -d 0.85

# Exemplo de uso do Kruskal
./kruskal -f examples/weighted_graph.txt -s

# Exemplo de uso do Dijkstra
./dijkstra -f examples/weighted_graph.txt -s 1
```

## 📋 Formato de Arquivos de Entrada

### Grafos Não-Ponderados
```
n m
u1 v1
u2 v2
...
um vm
```

### Grafos Ponderados
```
n m
u1 v1 w1
u2 v2 w2
...
um vm wm
```

**Onde:**
- `n` = número de vértices
- `m` = número de arestas
- `ui vi` = aresta entre vértices ui e vi
- `wi` = peso da aresta (quando aplicável)

**Observações:**
- Vértices são numerados de 1 a n
- Para grafos direcionados, `ui → vi` indica direção
- Pesos podem ser inteiros ou decimais conforme o algoritmo

## 🛠️ Build System e Opções

### Targets do Makefile

```bash
make all        # Compila todos os algoritmos
make clean      # Remove binários e arquivos temporários
```

### Opções Comuns de Linha de Comando

| Opção | Descrição | Algoritmos |
|-------|-----------|------------|
| `-f <arquivo>` | Arquivo de entrada (obrigatório) | Todos |
| `-o <arquivo>` | Arquivo de saída (opcional) | Todos |
| `-h` | Exibe ajuda detalhada | Todos |
| `-s` | Modo detalhado/verbose | Kruskal, Dijkstra |
| `-k <n>` | Top-k resultados | PageRank |
| `-d <valor>` | Fator de amortecimento | PageRank |

## 🧪 Testes Automatizados

O projeto inclui scripts de teste abrangentes para validação e demonstração:

### Executando Testes

```bash
cd tests/

# Testes do PageRank
chmod +x tests.sh
./tests.sh

# Testes de Componentes Fortemente Conexas (Kosaraju)
chmod +x tests.sh  
./tests.sh

# Testes de Árvore Geradora Mínima (Prim/Kruskal)
chmod +x tests.sh
./tests.sh
```

### O que os Testes Validam

- ✅ **Correção algorítmica** com casos conhecidos
- ✅ **Tratamento de casos extremos** (grafos vazios, desconexos)
- ✅ **Performance** em grafos de diferentes tamanhos
- ✅ **Consistência de saída** entre execuções
- ✅ **Validação de parâmetros** de entrada

## 📊 Análise de Complexidade


## 🎯 Exemplos de Uso Avançado

### Análise de Redes Sociais
```bash
# Calcular PageRank para identificar usuários influentes
./pagerank -f social_network.txt -k 20 -d 0.9

# Encontrar comunidades através de componentes fortemente conexas
./kosaraju -f social_network.txt
```

### Otimização de Redes
```bash
# Encontrar infraestrutura mínima para conectar cidades
./kruskal -f cities_network.txt -s -o minimal_infrastructure.txt

# Calcular rotas ótimas de distribuição
./dijkstra -f delivery_network.txt -s 1 -o optimal_routes.txt
```

### Análise de Dependências
```bash
# Detectar dependências circulares em sistemas
./kosaraju -f dependency_graph.txt

# Ordem topológica para build systems
./dijkstra -f build_dependencies.txt
```

## 🤝 Contribuindo

Contribuições são bem-vindas! Para contribuir:

1. **Fork** o repositório
2. Crie uma **branch** para sua feature (`git checkout -b feature/nova-feature`)
3. **Commit** suas mudanças (`git commit -am 'Adiciona nova feature'`)
4. **Push** para a branch (`git push origin feature/nova-feature`)
5. Abra um **Pull Request**

### Diretrizes para Contribuição

- ✅ Mantenha consistência de estilo com o código existente
- ✅ Adicione testes para novas funcionalidades
- ✅ Documente mudanças significativas
- ✅ Otimize para performance quando possível
- ✅ Inclua exemplos de uso para novos algoritmos

## 📚 Algoritmos Futuros

Algoritmos planejados para próximas versões:

- **Bellman-Ford**: Caminho mínimo com pesos negativos
- **Floyd-Warshall**: Todos os caminhos mínimos
- **Ford-Fulkerson**: Fluxo máximo
- **Edmonds-Karp**: Fluxo máximo otimizado
- **Tarjan**: Componentes fortemente conexas (alternativa)
- **A***: Busca heurística informada
- **Hierholzer**: Circuito Euleriano
- **Edmonds**: Matching de peso máximo

## Atualizações futuras 

### Comparação de Algoritmos de MST

| Aspecto | Prim | Kruskal |
|---------|------|---------|
| **Complexidade** | O(E log V) | O(E log E) |
| **Melhor para** | Grafos densos | Grafos esparsos |
| **Estrutura chave** | Heap | Union-Find |
| **Memória** | O(V) | O(E) |

### Algoritmos de Caminho Mínimo

| Algoritmo | Complexidade | Limitações | Casos de Uso |
|-----------|--------------|------------|--------------|
| **Dijkstra** | O((V+E) log V) | Pesos ≥ 0 | GPS, redes |
| **Bellman-Ford** | O(VE) | Detecta ciclos negativos | Economia, arbitragem |
| **Floyd-Warshall** | O(V³) | Todos os pares | Análise de alcançabilidade |


## 📖 Referências e Bibliografia

### Teoria dos Grafos
- **"Introduction to Algorithms"** - Cormen, Leiserson, Rivest, Stein (CLRS)
- **"Algorithm Design"** - Kleinberg, Tardos
- **"Graph Theory"** - Bondy, Murty

### Algoritmos Específicos
- **PageRank**: [https://pt.wikipedia.org/wiki/PageRank](https://pt.wikipedia.org/wiki/PageRank)
- **Kruskal**: [https://pt.wikipedia.org/wiki/Algoritmo_de_Kruskal](https://pt.wikipedia.org/wiki/Algoritmo_de_Kruskal)



## 📄 Licença

Este projeto está licenciado sob a licença MIT - veja o arquivo [LICENSE](LICENSE) para detalhes.

## 🔗 Links Úteis

- 📧 **Suporte**: [Abrir uma issue](https://github.com/EdeilsonAzevedo/graph-algorithms-cpp/issues)
- 🌟 **Contribuir**: [Guia de contribuição](#-contribuindo)
- 📖 **Documentação**: READMEs individuais de cada algoritmo
- 🧪 **Testes**: Scripts automatizados na pasta `tests/`

---

**Desenvolvido com ❤️ para a comunidade de algoritmos em grafos**