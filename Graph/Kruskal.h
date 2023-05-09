#pragma once

#include "graph.h"

class Kruskal
{
private:
    vector<int> weighs;
    vector<int> weighs_counts;
    vector<vector<int>> result;
    vector<vector<vector<int>>> edges;

    graph* G = NULL;

    int last = -1;

    bool is_not_in_weighs(int value);
    bool is_not_in_edges(int index, int x, int y);
    bool available_in_result(vector<int> vec);

    void set_result(vector<int> vec);
    void set_different_weighs();

    int get_index_from_weighs(int value);
    int get_index_from_result(int value);


protected:


public:
    Kruskal();
    ~Kruskal();
    Kruskal(graph* graf);

    void run();
};