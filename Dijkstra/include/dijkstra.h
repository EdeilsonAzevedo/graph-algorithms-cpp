#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <list>
#include <string>

using namespace std;

typedef pair<int, int> pii;

void dijkstra(vector<vector<pii>> &graph, int size, int initialVert, string outputPath);

#endif
