#pragma once

#include "graph.h"

class BFS
{
private:
    queue<int> queue;
    vector<int> colors;

    graph* G = NULL;

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