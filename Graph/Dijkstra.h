#pragma once

#include "graph.h"

class Dijkstra
{
private:
    deque<int> deque;
    vector<int> d;
    vector<int> p;

    graph* G = NULL;

    int item_count = 0;

    int w(int u, int v);
    void relax(int u, int v);


protected:


public:
    Dijkstra();
    ~Dijkstra();
    Dijkstra(graph* graf, int source_index);

    void run();
};