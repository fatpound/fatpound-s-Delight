#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <queue>

using namespace std;

class graph
{
private:
    class node
    {
    private:


    protected:


    public:
        vector<node*> next_list;
        int n = -1;

        node();
        ~node();

        void list_all_adj();
    };


protected:


public:
    vector<vector<int>> adj;
    vector<node*> all_nodes;

    graph();
    ~graph();
    graph(vector<vector<int>> vec);

    void list_all_nodes();
};