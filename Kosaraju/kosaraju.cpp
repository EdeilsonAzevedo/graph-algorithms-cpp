#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

vector<vector<int>> adj, adj_rev;
vector<bool> visited;
stack<int> finishStack;
vector<vector<int>> sccs;

void dfs1(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v])
            dfs1(v);
    }
    finishStack.push(u);
}

void dfs2(int u, vector<int>& component) {
    visited[u] = true;
    component.push_back(u + 1); // 1-based output
    for (int v : adj_rev[u]) {
        if (!visited[v])
            dfs2(v, component);
    }
}

void kosaraju(int n, ostream& out) {
    visited.assign(n, false);
    for (int i = 0; i < n; ++i)
        if (!visited[i])
            dfs1(i);

    visited.assign(n, false);
    while (!finishStack.empty()) {
        int u = finishStack.top();
        finishStack.pop();
        if (!visited[u]) {
            vector<int> component;
            dfs2(u, component);
            sort(component.begin(), component.end());
            sccs.push_back(component);
        }
    }

    sort(sccs.begin(), sccs.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    });

    for (const auto& comp : sccs) {
        for (int v : comp)
            out << v << " ";
        out << "\n";
    }
}

int main(int argc, char* argv[]) {
    string input_path, output_path;
    bool show_help = false;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-h") show_help = true;
        else if (arg == "-f" && i + 1 < argc) input_path = argv[++i];
        else if (arg == "-o" && i + 1 < argc) output_path = argv[++i];
        else {
            cerr << "Opção inválida: " << arg << "\n";
            return 1;
        }
    }

    if (show_help) {
        cout << "Uso: ./kosaraju -f <arquivo_entrada> [-o <arquivo_saida>]\n";
        cout << "Identifica componentes fortemente conexas em grafos direcionados.\n";
        return 0;
    }

    if (input_path.empty()) {
        cerr << "Erro: arquivo de entrada não especificado. Use -f <arquivo>\n";
        return 1;
    }

    ifstream infile(input_path);
    if (!infile) {
        cerr << "Erro ao abrir o arquivo de entrada: " << input_path << "\n";
        return 1;
    }

    ofstream outfile;
    ostream* out = &cout;
    if (!output_path.empty()) {
        outfile.open(output_path);
        if (!outfile) {
            cerr << "Erro ao abrir o arquivo de saída: " << output_path << "\n";
            return 1;
        }
        out = &outfile;
    }

    int n, m;
    infile >> n >> m;

    adj.assign(n, {});
    adj_rev.assign(n, {});

    for (int i = 0; i < m; ++i) {
        int u, v;
        infile >> u >> v;
        --u; --v; // ajusta para 0-based
        adj[u].push_back(v);
        adj_rev[v].push_back(u);
    }

    kosaraju(n, *out);
    return 0;
}
