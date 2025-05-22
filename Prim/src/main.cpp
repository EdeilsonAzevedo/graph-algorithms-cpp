#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>
#include <list>
#include <climits>

#include "../include/graph.h"
#include "../include/helper.h"

using namespace std;

int main(int argc, char **args)
{
    string inputPath, outputPath;
    int solution = 0, initialVert = 1;

    
    for (int i = 0; i < argc; i++)
    {
       
        if (!strcmp(args[i], "-f") && i != argc - 1)
        {
            inputPath = args[++i];
        }
        else if (!strcmp(args[i], "-f"))
        {
            printf("Um caminho para o arquivo precisa ser especificado apos '-f'\n");
            return 1;
        }

        
        if (!strcmp(args[i], "-o") && i != argc - 1)
        {
            outputPath = args[++i];
        }
        else if (!strcmp(args[i], "-o"))
        {
            printf("Um caminho para o arquivo de saida precisa ser especificado apos '-o'\n");
            return 1;
        }

       
        if (!strcmp(args[i], "-i") && i != argc - 1)
        {
            initialVert = stoi(args[++i]);
        }
        else if (!strcmp(args[i], "-i"))
        {
            printf("Um valor precisa ser informado para o vertice inicial apos '-i'\n");
            return 1;
        }

        
        if (!strcmp(args[i], "-s"))
        {
            solution = 1;
        }

        
        if (!strcmp(args[i], "-h"))
        {
            printHelper();
        }
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

    int vertices, arestas;
    stringstream ss(line);

    if (!(ss >> vertices >> arestas))
    {
        printf("Falha ao ler definicoes do grafo\n");
        return 1;
    }

    Graph g(vertices);

    // Adiciona arestas ao grafo
    for (int i = 0; i < arestas; i++)
    {
        if (!getline(inputFile, line))
        {
            printf("O input tem dados faltando\n");
            return 1;
        }

        int origem, destino, peso;
        stringstream ss(line);

        if (!(ss >> origem >> destino >> peso))
        {
            printf("Falha ao ler valores\n");
            return 1;
        }

        // Ajuste para indexação base 0
        g.addEdge(origem, destino, peso);
    }

    if (inputFile.is_open())
    {
        inputFile.close();
    }

    g.prim(initialVert - 1, solution, outputPath);
    return 0;
}
