#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <string>

using namespace std;

struct Edge
{
    int from, to, weight;
};

class Graph
{
public:
    int V;
    vector<list<pair<int, int>>> adj;
    vector<pair<int, int>> mstEdges;

    Graph(int V);

    void addEdge(int u, int v, int w);

    void prim(int initialVert, int solution, string outputPath);
};

#endif
