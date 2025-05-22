# PageRank

PageRank™ é um algoritmo utilizado pela ferramenta de busca Google para posicionar websites entre os resultados de suas buscas. O PageRank mede a importância de uma página contabilizando a quantidade e qualidade de links apontando para ela.

A métrica PageRank de uma página representa a probabilidade de uma pessoa chegar a essa página, clicando aleatoriamente em hiperligações. Em termos de teoria de grafos, o PageRank é uma métrica de centralidade que explora a estrutura de conexões para determinar a importância relativa de cada nó na rede.

## Modelagem Matemática

### Fórmula Base do PageRank

O valor de PageRank para uma página u pode ser expresso como:

```
PR(u) = Σ(PR(v) / L(v))
```

onde:
- `PR(u)` é o PageRank da página u
- `v` são todas as páginas que apontam para u
- `L(v)` é o número de links que saem da página v

### Fator de Amortecimento

A teoria de PageRank considera que um utilizador (ou surfista) imaginário que siga as ligações entre as páginas, aleatoriamente, acabará por se aborrecer e parar de seguir as ligações. A probabilidade, em cada passo, de o utilizador continuar a seguir as ligações é o fator de amortecimento d.

Com o fator de amortecimento, a fórmula completa do PageRank torna-se:

```
PR(u) = (1-d)/N + d × Σ(PR(v) / L(v))
```

onde:
- `d` é o fator de amortecimento (tradicionalmente 0.85)
- `N` é o número total de páginas na rede
- `(1-d)/N` representa a probabilidade de chegada aleatória à página

### Representação Matricial

O PageRank pode ser visto como um problema de autovetor, onde:

```
R = ((1-d)/N × E + d × M) × R
```

onde:
- `R` é o vetor de PageRank
- `M` é a matriz de transição normalizada
- `E` é uma matriz com todos os elementos iguais a 1

## Características do Algoritmo

### Convergência
O cálculo de PageRank é iterativo, ou seja, exige várias passagens, chamadas de "iterações", os valores obtidos em cada iteração convergem para os valores desejados de PageRank. O algoritmo termina quando a diferença entre iterações consecutivas é menor que um limiar predefinido.

### Tratamento de Nós Dangling
O algoritmo trata adequadamente os nós que não possuem links de saída (dangling nodes), redistribuindo seu PageRank uniformemente para todos os nós da rede.


### Opções Disponíveis ao executar o binario

- `-f <arquivo>`: Especifica o arquivo de entrada contendo o grafo (obrigatório)
- `-d <valor>`: Define o fator de amortecimento (padrão: 0.85, intervalo: 0.0 a 1.0)
- `-k <número>`: Número de vértices top-k a serem exibidos (padrão: 10)
- `-h`: Exibe a ajuda

### Formato do Arquivo de Entrada

O arquivo deve seguir o formato:
```
n m
u1 v1
u2 v2
...
um vm
```

onde:
- `n` = número de vértices
- `m` = número de arestas
- `ui vi` = aresta direcionada do vértice ui para vi

## Exemplo de Uso

```bash
# Executar com fator de amortecimento padrão (0.85) e mostrar top 10
./pagerank -f ../test/rc/inputs/g01.dat

# Executar com fator de amortecimento 0.9 e mostrar top 5
./pagerank -f ../test/rc/inputs/g01.dat -d 0.9 -k 5

# Exibir ajuda
./pagerank -h
```

## Parâmetros de Configuração

- **Fator de Amortecimento Padrão**: 0.85
- **Critério de Convergência**: 1e-8
- **Máximo de Iterações**: 100
- **Valor Inicial**: 1/n para cada nó

## Saída

O programa exibe os top-k vértices ordenados por PageRank em ordem decrescente:

```
Vértice 5: 0.234567
Vértice 2: 0.189234
Vértice 1: 0.145678
...
```

## Complexidade

- **Tempo por iteração**: O(m + n), onde m é o número de arestas e n o número de vértices
- **Espaço**: O(n + m) para armazenar o grafo e os vetores de PageRank
- **Convergência**: Tipicamente 50-100 iterações para grafos reais

## Implementação

O algoritmo implementa o método de potência (power method) para encontrar o autovetor dominante da matriz de transição modificada. A implementação é otimizada para:

1. **Eficiência de memória**: Usa apenas dois vetores para alternar entre iterações
2. **Tratamento de dangling nodes**: Distribui o PageRank acumulado uniformemente
3. **Normalização**: Garante que a soma dos PageRanks seja sempre 1
4. **Convergência robusta**: Monitora a variação L1 entre iterações

Este algoritmo é fundamental para sistemas de ranking em grafos e tem aplicações em análise de redes sociais, sistemas de recomendação e motores de busca.

## Referências
    PageRank - Wikipedia: https://pt.wikipedia.org/wiki/PageRank
Fonte principal para a modelagem matemática e fundamentação teórica do algorirtimo