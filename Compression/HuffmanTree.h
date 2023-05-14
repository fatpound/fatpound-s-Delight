#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <queue>

class HuffmanTree
{
private:
    class node
    {
    private:


    protected:


    public:
        HuffmanTree::node* left = nullptr;
        HuffmanTree::node* right = nullptr;

        int num = 0;
        char k = '\0';

        node();
        ~node();
        node(char new_k, int new_num);
        node(HuffmanTree::node* sol, HuffmanTree::node* sag);
    };

    void list_preorder_private(HuffmanTree::node* node);


protected:


public:
    HuffmanTree::node* root = nullptr;

    int node_count = 0;

    void list_preorder();

    HuffmanTree();
    ~HuffmanTree();
    HuffmanTree(std::vector<std::array<int, 2>> vec);
};
