#pragma once

#include "graph.h"

class DFS
{
private:
    std::vector<int> colors;

    graph* G = NULL;

    static int color_white;
    static int color_gray;
    static int color_black;

    void visit(int index);


protected:


public:
    DFS();
    ~DFS();
    DFS(graph* graf);

    void run();
};