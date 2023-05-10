#pragma once

#include "graph.h"

class Prim
{
private:
    std::deque<int> deque;

    std::vector<int> key;
    std::vector<int> pi;

    graph* G = nullptr;

    int item_count = 0;


protected:


public:
    Prim();
    ~Prim();
    Prim(graph* graf);

    void run();
};