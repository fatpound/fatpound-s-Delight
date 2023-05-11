#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <queue>

#include "graph_reader.h"

class graph
{
private:
    class node
    {
    private:


    protected:


    public:
        std::vector<node*> next_list;
        int n = -1;

        node();
        ~node();

        void list_all_adj();
    };


protected:


public:
    std::vector<std::vector<int>> adj;
    std::vector<node*> nodes;

    int node_count = 0;
    int edge_count = 0;

    graph();
    ~graph();
    graph(std::string);
    graph(std::vector<std::vector<int>> vec);

    void list_nodes();
};