#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <string>

using namespace std;

// Define o tipo da aresta como (peso, origem, destino)
using Edge = tuple<int, int, int>;

/**
 * Lê n vértices e m arestas de um istream,
 * armazena as arestas como tuplas e as ordena pelo peso.
 */
vector<Edge> read_and_sort_edges(istream& in, int& num_vertices, int& num_edges) {
    in >> num_vertices >> num_edges;
    vector<Edge> edges;
    edges.reserve(num_edges);

    for (int i = 0; i < num_edges; ++i) {
        int u, v, w;
        in >> u >> v >> w;
        edges.emplace_back(w, u - 1, v - 1);
    }

    sort(edges.begin(), edges.end());
    return edges;
}

// Estrutura de Union-Find (DSU)
struct DSU {
    vector<int> parent, rank;
    DSU(int n): parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    int find(int u) {
        return parent[u] == u ? u : parent[u] = find(parent[u]);
    }
    bool unite(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) return false;
        if (rank[u] < rank[v]) parent[u] = v;
        else if (rank[v] < rank[u]) parent[v] = u;
        else { parent[v] = u; rank[u]++; }
        return true;
    }
};

// Kruskal: retorna custo total + lista de arestas da MST
pair<int, vector<Edge>> kruskal(int num_vertices, const vector<Edge>& edges) {
    DSU dsu(num_vertices);
    vector<Edge> mst;
    int total_cost = 0;
    for (auto& [w,u,v] : edges) {
        if (dsu.unite(u,v)) {
            mst.emplace_back(w,u,v);
            total_cost += w;
        }
    }
    return { total_cost, mst };
}

// Carrega e imprime o arquivo de ajuda
void print_help(const string& help_path) {
    ifstream help_file(help_path);
    if (!help_file) {
        cerr << "Erro ao abrir ajuda: " << help_path << endl;
        return;
    }
    cout << help_file.rdbuf();
}

int main(int argc, char* argv[]) {
    string in_path, out_path;
    bool flag_s = false, flag_h = false;

    // Parse simples de argv
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-f" && i+1 < argc) {
            in_path = argv[++i];
        }
        else if (arg == "-o" && i+1 < argc) {
            out_path = argv[++i];
        }
        else if (arg == "-s") {
            flag_s = true;
        }
        else if (arg == "-h") {
            flag_h = true;
        }
        else {
            cerr << "Opção desconhecida: " << arg << "\nUse -h para ajuda.\n";
            return 1;
        }
    }

    if (flag_h) {
        print_help("../helps/kruskal_help.txt");
        return 0;
    }
    if (in_path.empty()) {
        cerr << "Erro: arquivo de entrada não especificado. Use -f <arquivo>.\n";
        return 1;
    }

    // Configura streams de entrada e saída
    ifstream infile(in_path);
    if (!infile) {
        cerr << "Não foi possível abrir entrada: " << in_path << endl;
        return 1;
    }
    ostream* out = &cout;
    ofstream outfile;
    if (!out_path.empty()) {
        outfile.open(out_path);
        if (!outfile) {
            cerr << "Não foi possível abrir saída: " << out_path << endl;
            return 1;
        }
        out = &outfile;
    }

    // Leitura, execução e impressão de resultados
    int n, m;
    auto edges = read_and_sort_edges(infile, n, m);
    auto [cost, mst] = kruskal(n, edges);

    (*out) << cost << endl;
    if (flag_s) {
        for (auto& [w,u,v] : mst) {
            // imprime em 1-based
            (*out) << "(" << u+1 << "," << v+1 << ") ";
        }
        (*out) << endl;
    }

    return 0;
}
