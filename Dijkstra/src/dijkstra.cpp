#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <fstream>

#include "../include/dijkstra.h"

typedef pair<int, int> pii;

using namespace std;

void dijkstra(vector<vector<pii>> &graph, int size, int initialVert, string outputPath)
{
    ofstream outFile(outputPath);

    vector<int> dist(size, INT_MAX);
    dist[initialVert] = 0;

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, initialVert});

    while (!pq.empty())
    {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u])
        {
            continue;
        }

        for (auto &edge : graph[u])
        {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    for (int i = 0; i < size; i++)
    {
        int distance = dist[i] == INT_MAX ? -1 : dist[i];

        if (outFile.is_open())
        {
            outFile << i + 1 << ":" << distance << " ";
        }
        else
        {
            printf("%i:%i ", i + 1, distance);
        }
    }

    if (outFile.is_open())
    {
        outFile << endl;
        outFile.close();
    }
    else
    {
        printf("\n");
    }
}