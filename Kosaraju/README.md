# Algoritmo de Kosaraju 

## O que são Componentes Fortemente Conexas?

Uma **Componente Fortemente Conexa** é um subconjunto maximal de vértices de um grafo direcionado onde existe um caminho direcionado de qualquer vértice para qualquer outro vértice dentro do mesmo subconjunto.

Em outras palavras, em uma componente fortemente conexa:
- Para todo par de vértices (u, v), existe um caminho de u para v
- Para todo par de vértices (u, v), existe um caminho de v para u
- O subconjunto é maximal (não pode ser estendido mantendo a propriedade)

## Algoritmo de Kosaraju

O algoritmo de Kosaraju foi desenvolvido por S. Rao Kosaraju em 1978 e redescoberto independentemente por Micha Sharir em 1981. É um algoritmo elegante e eficiente que resolve o problema das componentes fortemente conexas em tempo linear.

### Fundamentação Teórica

O algoritmo baseia-se em duas observações fundamentais:
1. **Propriedade do Grafo Transposto**: O grafo transposto G^T (onde todas as arestas são invertidas) possui exatamente as mesmas componentes fortemente conexas que o grafo original G
2. **Propriedade da Ordem de Finalização**: A ordem em que os vértices terminam de ser visitados em uma DFS revela informações sobre a estrutura das componentes

### Funcionamento do Algoritmo

O algoritmo de Kosaraju executa em **duas fases**:

#### Fase 1: DFS no Grafo Original
1. Execute DFS no grafo original G
2. À medida que cada vértice termina de ser visitado, empilhe-o
3. Ao final, temos uma pilha com vértices em ordem de pós-ordem

#### Fase 2: DFS no Grafo Transposto
1. Construa o grafo transposto G^T (inverta todas as arestas)
2. Desempilhe vértices da pilha da Fase 1
3. Para cada vértice desempilhado ainda não visitado:
   - Execute DFS em G^T a partir desse vértice
   - Todos os vértices alcançados formam uma componente fortemente conexa

## Modelagem Matemática

### Definição Formal

Seja G = (V, E) um grafo direcionado onde:
- V é o conjunto de vértices com |V| = n
- E é o conjunto de arestas direcionadas com |E| = m

Uma componente fortemente conexa C ⊆ V satisfaz:
```
∀u,v ∈ C: ∃ caminho u → v ∧ ∃ caminho v → u
```

### Relação de Equivalência

A **ligação forte** entre vértices é uma relação de equivalência:
- **Reflexiva**: Todo vértice está fortemente ligado a si mesmo
- **Simétrica**: Se u está fortemente ligado a v, então v está fortemente ligado a u  
- **Transitiva**: Se u está fortemente ligado a v e v a w, então u está fortemente ligado a w

### Grafo das Componentes (DAG)

O grafo das componentes D(G) é um DAG (Directed Acyclic Graph) onde:
- Cada nó representa uma componente fortemente conexa
- Existe uma aresta entre componentes C₁ e C₂ se há arestas de vértices em C₁ para vértices em C₂

### Propriedade da Pós-Ordem

**Lema fundamental**: Se u e v pertencem a componentes diferentes e existe aresta u → v, então post[u] > post[v], onde post[·] é a numeração em pós-ordem da DFS.

Esta propriedade garante que processar vértices em ordem decrescente de pós-ordem permite identificar corretamente as componentes.

### Complexidade

- **Tempo**: O(V + E) - linear no tamanho do grafo
  - DFS no grafo original: O(V + E)
  - Construção do grafo transposto: O(V + E)  
  - DFS no grafo transposto: O(V + E)
- **Espaço**: O(V + E) para armazenar grafo original, transposto e estruturas auxiliares

## Como Usar

### Compilação
```bash
make all
```

### Execução
```bash
./kosaraju -f <arquivo_grafo> [-o <arquivo_saida>]
```

### Opções Disponíveis

- `-f <arquivo>`: Especifica o arquivo de entrada contendo o grafo direcionado (obrigatório)
- `-o <arquivo>`: Define arquivo de saída (opcional, padrão: stdout)
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
- `m` = número de arestas direcionadas
- `ui vi` = aresta direcionada do vértice ui para vi

**Nota**: Os vértices são numerados de 1 a n no arquivo de entrada.

## Exemplo de Uso

### Arquivo de entrada (grafo.dat):
```
6 7
1 2
2 3
3 1
3 4
4 5
5 6
6 4
```

### Execução:

```bash
# Mostrar componentes na saída padrão
./kosaraju -f grafo.dat

# Exemplo de saída:
# 1 2 3
# 4 5 6

# Salvar resultado em arquivo
./kosaraju -f grafo.dat -o componentes.txt

# Exibir ajuda
./kosaraju -h
```

## Características da Implementação

### Eficiência
- **Duas DFS completas**: Uma no grafo original, outra no transposto
- **Construção eficiente do transposto**: Armazenado em lista de adjacência
- **Ordenação automática**: Componentes ordenadas pelo menor vértice

### Saída Organizada
- **Componentes ordenadas**: Por menor vértice de cada componente
- **Vértices ordenados**: Dentro de cada componente em ordem crescente
- **Formato limpo**: Uma componente por linha, vértices separados por espaço

### Tratamento de Casos
- **Grafos desconexos**: Funciona corretamente
- **Componentes unitárias**: Vértices isolados são tratados como componentes de tamanho 1
- **Grafos grandes**: Eficiência linear permite processar grafos extensos

## Aplicações Práticas

### Análise de Redes
- **Redes sociais**: Identificar grupos de usuários mutuamente conectados
- **World Wide Web**: Encontrar clusters de páginas inter-relacionadas
- **Sistemas de recomendação**: Detectar grupos com interesses similares

### Engenharia de Software
- **Análise de dependências**: Detectar dependências circulares em módulos
- **Compiladores**: Otimização de código baseada na estrutura de dependências
- **Refatoração**: Identificar blocos de código fortemente acoplados

### Análise de Sistemas
- **Detecção de deadlocks**: Identificar ciclos em grafos de recursos
- **Análise de fluxo**: Componentes que se auto-sustentam
- **Teoria de jogos**: Identificar coalizões estáveis

## Comparação com Outros Algoritmos

| Aspecto | Kosaraju | Tarjan |
|---------|----------|---------|
| **Complexidade** | O(V + E) | O(V + E) |
| **Número de DFS** | 2 | 1 |
| **Grafo transposto** | Necessário | Não necessário |
| **Simplicidade** | Alto | Médio |
| **Uso de memória** | 2×(V + E) | V + E |

### Vantagens do Kosaraju
- ✅ **Simplicidade conceitual**: Algoritmo intuitivo e fácil de entender
- ✅ **Implementação direta**: Menos propenso a erros de implementação
- ✅ **Debugging facilidade**: Cada fase pode ser analisada separadamente

### Quando Usar Kosaraju
- Quando a simplicidade é prioritária
- Para fins educacionais e didáticos
- Quando a construção do grafo transposto não é custosa
- Em grafos onde a estrutura é analisada múltiplas vezes

## Exemplo de Análise Passo a Passo

### Grafo de Entrada:
```
4 5
1 2
2 3
3 1
2 4
4 2
```

### Fase 1 - DFS no Grafo Original:
1. Iniciar DFS de 1: 1 → 2 → 3 → volta para 2 → 4 → volta
2. Ordem de finalização: [3, 4, 2, 1]
3. Pilha: [1, 2, 4, 3] (topo → base)

### Fase 2 - DFS no Grafo Transposto:
1. Grafo transposto: 2→1, 3→2, 1→3, 4→2, 2→4
2. DFS de 1: visita {1, 3, 2} → Componente 1
3. DFS de 4: visita {4} → Componente 2

**Resultado**: {1, 2, 3} e {4}

## Variações e Extensões

### Kosaraju Modificado
- **Numeração de componentes**: Atribuir ID único para cada componente
- **Contagem apenas**: Retornar apenas o número de componentes
- **Grafo das componentes**: Construir explicitamente o DAG das componentes

### Aplicações Avançadas
- **Condensação**: Criar grafo condensado das componentes
- **Análise de alcançabilidade**: Determinar quais componentes alcançam outras
- **Componentes fonte/sorvedouro**: Identificar componentes sem entrada/saída

## Limitações e Considerações

### Restrições
- ⚠️ **Apenas grafos direcionados**: Não se aplica a grafos não-direcionados
- ⚠️ **Memória extra**: Requer armazenamento do grafo transposto
- ⚠️ **Duas passagens**: Não adequado para grafos dinâmicos

### Otimizações Possíveis
- **Lazy transpose**: Construir transposto sob demanda
- **Compressed representation**: Usar representação compacta para grafos esparsos
- **Parallel version**: Versão paralela para grafos muito grandes

## Testes e Validação

O algoritmo pode ser testado com:
- **Grafos fortemente conexos**: Deve retornar uma única componente
- **DAGs**: Cada vértice deve ser uma componente separada
- **Grafos desconexos**: Múltiplas componentes independentes
- **Casos extremos**: Grafos com 1 vértice, grafos vazios

## Referências

- **Algoritmo de Kosaraju-Sharir**: [https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/kosaraju.html](https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/kosaraju.html)
  - Fonte principal para a fundamentação teórica e modelagem matemática
