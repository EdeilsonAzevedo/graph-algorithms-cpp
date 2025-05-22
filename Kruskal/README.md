# Kruskal 

## O que é uma Árvore Geradora Mínima?

Uma **Árvore Geradora Mínima** é um subconjunto das arestas de um grafo conexo e ponderado que:
- Conecta todos os vértices do grafo
- Forma uma árvore (grafo conexo e acíclico)
- Possui a menor soma possível dos pesos das arestas

Se o grafo não for conexo, o algoritmo encontra uma **Floresta Geradora Mínima** (uma árvore geradora mínima para cada componente conexo do grafo).

## Algoritmo de Kruskal

O algoritmo de Kruskal é um **algoritmo guloso** (greedy) que foi desenvolvido por Joseph Kruskal em 1956. Ele constrói a MST selecionando as arestas de menor peso que não formam ciclos.

### Funcionamento do Algoritmo

1. **Inicialização**: Crie uma floresta F onde cada vértice é uma árvore separada
2. **Ordenação**: Ordene todas as arestas do grafo em ordem crescente de peso
3. **Iteração**: Para cada aresta na ordem crescente:
   - Se a aresta conecta duas árvores diferentes, adicione-a à floresta
   - Caso contrário, descarte a aresta (pois formaria um ciclo)
4. **Finalização**: O algoritmo termina quando a floresta tem apenas um componente

## Modelagem Matemática

### Definição Formal

Seja G = (V, E) um grafo conexo e ponderado, onde:
- V é o conjunto de vértices com |V| = n
- E é o conjunto de arestas com |E| = m
- w: E → ℝ é a função peso das arestas

Uma árvore geradora T é um subgrafo de G tal que:
- T é conexo e acíclico
- T contém todos os vértices de V
- T possui exatamente n-1 arestas

### Problema da MST

O problema da MST consiste em encontrar uma árvore geradora T* tal que:

```
T* = argmin Σ w(e)
     T∈𝒯   e∈T
```

onde 𝒯 é o conjunto de todas as árvores geradoras possíveis de G.

### Invariante do Algoritmo

O algoritmo de Kruskal mantém a seguinte invariante:
- **Propriedade de Corte**: Para qualquer corte (S, V-S) que separe dois componentes da floresta atual, a aresta de menor peso cruzando esse corte é segura para a MST.

### Estrutura Union-Find (DSU)

O algoritmo utiliza a estrutura de dados **Disjoint Set Union** para verificar eficientemente se duas arestas pertencem ao mesmo componente:

- **Find(u)**: Encontra o representante do conjunto que contém u
- **Union(u,v)**: Une os conjuntos que contêm u e v
- **Otimizações**: 
  - Compressão de caminho no Find
  - União por rank no Union

### Complexidade

- **Tempo**: O(m log m) onde m é o número de arestas
  - Ordenação das arestas: O(m log m)
  - Operações Union-Find: O(m α(n)) ≈ O(m)
- **Espaço**: O(n + m) para armazenar o grafo e estruturas auxiliares

## Como Usar

### Compilação
```bash
make all
```

### Execução
```bash
./kruskal -f <arquivo_grafo> [opções]
```

### Opções Disponíveis

- `-f <arquivo>`: Especifica o arquivo de entrada contendo o grafo (obrigatório)
- `-o <arquivo>`: Define arquivo de saída (opcional, padrão: stdout)
- `-s`: Exibe as arestas da MST em vez de apenas o custo total
- `-h`: Exibe a ajuda

### Formato do Arquivo de Entrada

O arquivo deve seguir o formato:
```
n m
u1 v1 w1
u2 v2 w2
...
um vm wm
```

onde:
- `n` = número de vértices
- `m` = número de arestas  
- `ui vi wi` = aresta entre vértices ui e vi com peso wi

**Nota**: Os vértices são numerados de 1 a n no arquivo de entrada.

## Exemplo de Uso

### Arquivo de entrada (../test/agm/inputs/brock200-1.mtx):
```
4 5
1 2 10
2 3 6
3 4 5
4 1 15
1 3 4
```

### Execuções:

```bash
# Mostrar apenas o custo total da MST
./kruskal -f ../test/agm/inputs/brock200-1.mtx
# Saída: 15

# Mostrar as arestas da MST
./kruskal -f ../test/agm/inputs/brock200-1.mtx -s
# Saída: (1,3) (3,4) (2,3) 

# Salvar resultado em arquivo
./kruskal -f ../test/agm/inputs/brock200-1.mtx -o resultado.txt

# Exibir ajuda
./kruskal -h
```

## Características da Implementação

### Eficiência
- **Ordenação otimizada**: Usa `std::sort` para ordenar as arestas
- **Union-Find otimizado**: Implementa compressão de caminho e união por rank
- **Memória eficiente**: Armazena arestas como tuplas (peso, origem, destino)

### Robustez
- **Validação de entrada**: Verifica se o arquivo existe e está formatado corretamente
- **Tratamento de grafos desconexos**: Funciona corretamente em grafos não-conexos
- **Normalização de índices**: Converte índices de vértices (1-based para 0-based)

### Saída Flexível
- **Modo compacto**: Apenas o custo total (padrão)
- **Modo detalhado** (`-s`): Lista todas as arestas da MST
- **Redirecionamento**: Suporte para arquivo de saída

## Aplicações Práticas

- **Redes de telecomunicações**: Conectar cidades com custo mínimo de cabeamento
- **Redes de energia**: Minimizar custo de transmissão elétrica
- **Logística**: Otimizar rotas de distribuição
- **Clustering**: Algoritmos de agrupamento hierárquico
- **Aproximação**: Base para algoritmos de aproximação (TSP, Steiner Tree)

## Complexidade Detalhada

### Análise Temporal
1. **Leitura e ordenação**: O(m log m)
2. **Inicialização DSU**: O(n)  
3. **Processamento das arestas**: O(m α(n))
4. **Total**: O(m log m + n + m α(n)) = O(m log m)

### Análise Espacial
- **Armazenamento das arestas**: O(m)
- **Estrutura Union-Find**: O(n)
- **Vetores auxiliares**: O(n)
- **Total**: O(n + m)

onde α(n) é a função inversa de Ackermann (praticamente constante para valores práticos).

## Referências

- **Algoritmo de Kruskal - Wikipedia**: [https://pt.wikipedia.org/wiki/Algoritmo_de_Kruskal](https://pt.wikipedia.org/wiki/Algoritmo_de_Kruskal)
  - Fonte principal para a fundamentação teórica e definições do algoritmo