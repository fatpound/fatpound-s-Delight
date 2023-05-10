#pragma once

#include "graph.h"

class BFS
{
private:
    std::queue<int> queue;
    std::vector<int> colors;

    graph* G = nullptr;

    static int color_white;
    static int color_gray;
    static int color_black;


protected:


public:
    BFS();
    ~BFS();
    BFS(graph* graf);

    void run();
};