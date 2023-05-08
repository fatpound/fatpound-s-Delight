#pragma once

#include "graph.h"

class BellmanFord
{
private:
    array<vector<array<int, 2>>, 3> edges;
    vector<int> d;
    vector<int> p;

    graph* G = NULL;

    int w(int u, int v);
    void relax(int u, int v);


protected:


public:
    BellmanFord();
    ~BellmanFord();
    BellmanFord(graph* graf, int source_index);

    bool run();
};