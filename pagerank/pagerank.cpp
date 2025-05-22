#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <numeric>
#include <string>
#include <algorithm>

using namespace std;

const double DEFAULT_DAMPING = 0.85;
const double EPS = 1e-8;
const int MAX_ITER = 100;

void print_help(const string& help_path) {
    ifstream help_file(help_path);
    if (!help_file) {
        cerr << "Erro ao abrir arquivo de ajuda: " << help_path << endl;
        return;
    }
    cout << help_file.rdbuf();
}

int main(int argc, char* argv[]) {
    string input_path;
    string help_path = "../helps/pagerank_help.txt";
    int top_k = 10;
    double damping = DEFAULT_DAMPING;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-h") {
            print_help(help_path);
            return 0;
        } else if (arg == "-f" && i + 1 < argc) {
            input_path = argv[++i];
        } else if (arg == "-d" && i + 1 < argc) {
            damping = stod(argv[++i]);
            if (damping < 0.0 || damping > 1.0) {
                cerr << "Fator de amortecimento deve estar entre 0 e 1.\n";
                return 1;
            }
        } else if (arg == "-k" && i + 1 < argc) {
            top_k = stoi(argv[++i]);
            if (top_k <= 0) {
                cerr << "O número de vértices a exibir deve ser positivo.\n";
                return 1;
            }
        } else {
            cerr << "Argumento inválido: " << arg << "\nUse -h para ajuda.\n";
            return 1;
        }
    }

    if (input_path.empty()) {
        cerr << "Erro: arquivo de entrada não especificado. Use -f <arquivo>\n";
        return 1;
    }

    ifstream infile(input_path);
    if (!infile) {
        cerr << "Erro ao abrir arquivo: " << input_path << endl;
        return 1;
    }

    int n, m;
    infile >> n >> m;

    if (top_k > n) {
        cerr << "Erro: valor de -k excede o número de vértices no grafo (" << n << ").\n";
        return 1;
    }

    vector<vector<int>> adj(n);
    vector<int> out_degree(n, 0);

    for (int i = 0; i < m; ++i) {
        int u, v;
        infile >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        out_degree[u]++;
    }

    vector<double> pr(n, 1.0 / n), pr_next(n);

    for (int iter = 0; iter < MAX_ITER; ++iter) {
        fill(pr_next.begin(), pr_next.end(), (1.0 - damping) / n);

        double dangling_sum = 0.0;
        for (int u = 0; u < n; ++u) {
            if (out_degree[u] == 0) {
                dangling_sum += pr[u];
            } else {
                for (int v : adj[u]) {
                    pr_next[v] += damping * pr[u] / out_degree[u];
                }
            }
        }

        for (int v = 0; v < n; ++v) {
            pr_next[v] += damping * dangling_sum / n;
        }

        double diff = 0.0;
        for (int i = 0; i < n; ++i) {
            diff += fabs(pr_next[i] - pr[i]);
            pr[i] = pr_next[i];
        }

        if (diff < EPS) break;
    }

    // Normaliza
    double total = accumulate(pr.begin(), pr.end(), 0.0);
    for (double& val : pr) val /= total;

    // Ordena por rank
    vector<pair<int, double>> ranked;
    for (int i = 0; i < n; ++i)
        ranked.emplace_back(i + 1, pr[i]);

    sort(ranked.begin(), ranked.end(), [](auto& a, auto& b) {
        return b.second < a.second; // decrescente
    });

    for (int i = 0; i < top_k; ++i) {
        cout << "Vértice " << ranked[i].first << ": " << ranked[i].second << endl;
    }

    return 0;
}
