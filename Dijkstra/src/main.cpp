#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>
#include <list>
#include <climits>

#include "../include/dijkstra.h"
#include "../include/helper.h"

using namespace std;

int main(int argc, char **args)
{
    string inputPath, outputPath;
    int initialVert = 1;

    // Receber opcoes do usuario
    for (int i = 0; i < argc; i++)
    {
        // Indicar arquivo que contem o grafo de entrada
        if (!strcmp(args[i], "-f") && i != argc - 1)
        {
            inputPath = args[++i];
        }
        else if (!strcmp(args[i], "-f"))
        {
            printf("Um caminho para o arquivo precisa ser especificado apos '-f'\n");
            return 1;
        }

        // Indicar arquivo em que a saida sera armazenada (opcional)
        if (!strcmp(args[i], "-o") && i != argc - 1)
        {
            outputPath = args[++i];
        }
        else if (!strcmp(args[i], "-o"))
        {
            printf("Um caminho para o arquivo de saida precisa ser especificado apos '-o'\n");
            return 1;
        }

        // Indica o vertice inicial usado no algoritmo
        if (!strcmp(args[i], "-i") && i != argc - 1)
        {
            initialVert = stoi(args[++i]);
        }
        else if (!strcmp(args[i], "-i"))
        {
            printf("Um valor precisa ser informado para o vertice inicial apos '-i'\n");
            return 1;
        }

        // Verifica se o usuario precisa do helper
        if (!strcmp(args[i], "-h"))
        {
            printHelper();
        }
    }

    // Ler inputs do arquivo informado (-f <arquivo>)
    if (inputPath.empty()) {
        printf("Por favor, informe um arquivo de entrada (-f <arquivo>)\n");
        return 1;
    }

    ifstream inputFile(inputPath);

    if (!inputFile.is_open())
    {
        printf("O arquivo informado nao foi encontrado, verifique o caminho\n");
        return 1;
    }

    string line;

    if (!getline(inputFile, line))
    {
        printf("Falha ao ler inputs do usuario\n");
        return 1;
    }

    int size, edges;
    stringstream ss(line);

    if (!(ss >> size >> edges))
    {
        printf("Falha ao ler definicoes do grafo\n");
        return 1;
    }

    vector<vector<pii>> graph(size);

    // Adiciona edges ao grafo
    for (int i = 0; i < edges; i++)
    {
        if (!getline(inputFile, line))
        {
            printf("O input tem dados faltando\n");
            return 1;
        }

        int from, to, weight;
        stringstream ss(line);

        if (!(ss >> from >> to >> weight))
        {
            printf("Falha ao ler valores\n");
            return 1;
        }

        // Adicionar arestas
        from -= 1;
        to -= 1;

        graph[from].push_back({to, weight});
        graph[to].push_back({from, weight});
    }

    if (inputFile.is_open())
    {
        inputFile.close();
    }

    dijkstra(graph, size, --initialVert, outputPath);
    return 0;
}
