#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;


// Define o tipo da aresta como (peso, origem, destino)
using Edge = tuple<int, int, int>;

/**
 * Lê n vértices e m arestas com peso da entrada padrão,
 * armazena as arestas como tuplas e as ordena pelo peso.
 */
vector<Edge> read_and_sort_edges(int& num_vertices, int& num_edges) {
    cin >> num_vertices >> num_edges;

    vector<Edge> edges;

    for (int i = 0; i < num_edges; ++i) {
        int u, v, w;
        cin >> u >> v >> w;

        // Subtrai 1 para usar índices baseados em 0
        edges.emplace_back(w, u - 1, v - 1);
    }

    // Ordena as arestas por peso (primeiro elemento da tupla)
    sort(edges.begin(), edges.end()); // O(n log n)

    return edges;
}

// Estrutura de Union-Find (Disjoint Set Union - DSU)
struct DSU {
    vector<int> parent, rank;

    DSU(int n) {
        parent.resize(n);
        rank.assign(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    // Encontra o representante (com compressão de caminho)
    int find(int u) {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    // Une dois conjuntos
    bool unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;

        if (rank[u] < rank[v])
            parent[u] = v;
        else if (rank[u] > rank[v])
            parent[v] = u;
        else {
            parent[v] = u;
            rank[u]++;
        }
        return true;
    }
};

// Algoritmo de Kruskal
pair<int, vector<Edge>> kruskal(int num_vertices, const vector<Edge>& edges) {
    DSU dsu(num_vertices);
    vector<Edge> mst;
    int total_cost = 0;

    for (const auto& [weight, u, v] : edges) {
        if (dsu.unite(u, v)) {
            mst.emplace_back(weight, u, v);
            total_cost += weight;
        }
    }

    return {total_cost, mst};
}

// Função principal
int main() {
    int n, m;
    vector<Edge> edges = read_and_sort_edges(n, m);

    auto [cost, mst] = kruskal(n, edges);

    cout << cost << endl; // imprime o custo total

    // Exibe as arestas da AGM
    for (auto [w, u, v] : mst)
        cout << "(" << u + 1 << "," << v + 1 << ") "; // volta para 1-based

    cout << endl;
    return 0;
}


