#pragma once

#include "graph.h"

class FloydWarshall
{
private:
    std::vector<std::vector<int>> result;

    graph* G = nullptr;
    

protected:


public:
    FloydWarshall();
    ~FloydWarshall();
    FloydWarshall(graph* graf);

    void run();
};