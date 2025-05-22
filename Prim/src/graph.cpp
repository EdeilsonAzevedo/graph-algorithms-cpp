#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <climits>
#include <string>
#include <fstream>

#include "../include/graph.h"

using namespace std;

// A estrutura em si está definida na header file (/include/graph.h)


Graph::Graph(int V)
{
    this->V = V;
    adj.resize(V);
}

void Graph::addEdge(int u, int v, int w)
{
    u -= 1;
    v -= 1;

    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

void Graph::prim(int initialVert, int solution, string outputPath)
{
    ofstream outfile(outputPath);

    vector<bool> inMST(V, false);
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    key[initialVert] = 0;
    pq.push(make_pair(0, initialVert));

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u])
            continue;

        inMST[u] = true;

        for (auto it = adj[u].begin(); it != adj[u].end(); ++it)
        {
            int v = it->first;
            int weight = it->second;

            if (!inMST[v] && key[v] > weight)
            {
                key[v] = weight;
                parent[v] = u;
                pq.push(make_pair(key[v], v));
            }
        }
    }

    // Calcula o custo total da AGM
    int totalWeight = 0;

    for (int i = 1; i < V; ++i)
    {
        totalWeight += key[i];
        mstEdges.push_back(make_pair(parent[i], i));
    }

   
    if (!solution && outfile.is_open())
    {
        outfile << totalWeight << endl;
        outfile.close();
    }
    else if (!solution)
    {
        printf("%i\n", totalWeight);
    }

    if (!solution)
        return;

   
    for (auto edge : mstEdges)
    {
        if (outfile.is_open())
        {
            outfile << "(" << edge.first + 1 << ", " << edge.second + 1 << ") ";
        }
        else
        {
            cout << "(" << edge.first + 1 << ", " << edge.second + 1 << ") ";
        }
    }

    if (!outfile.is_open())
    {
        cout << endl;
        return;
    }

    outfile << endl;
    outfile.close();
}
