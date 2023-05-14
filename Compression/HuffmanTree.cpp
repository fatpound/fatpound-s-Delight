#include "HuffmanTree.h"

HuffmanTree::node::node()
{

}
HuffmanTree::node::~node()
{

}
HuffmanTree::node::node(char new_k, int new_num)
{
    this->k = new_k;
    this->num = new_num;
}
HuffmanTree::node::node(HuffmanTree::node* sol, HuffmanTree::node* sag)
{
    this->k = '\0';
    this->num = sol->num + sag->num;

    this->left = sol;
    this->right = sag;
}

HuffmanTree::HuffmanTree()
{

}
HuffmanTree::~HuffmanTree()
{

}
HuffmanTree::HuffmanTree(std::vector<std::array<int, 2>> vec)
{
    std::deque<HuffmanTree::node*> deque;

    for (int i = 0; i < vec.size(); i++)
    {
        deque.push_back(new node((char)vec.at(i).at(0), vec.at(i).at(1)));
    }

    int n = deque.size();

    for (int i = 0; i < n - 1; i++)
    {
        HuffmanTree::node* sol = deque.at(0);
        HuffmanTree::node* sag = deque.at(1);
        
        HuffmanTree::node* yeni_dugum = new HuffmanTree::node(sol, sag);

        deque.pop_front();
        deque.pop_front();

        int index = 0;

        for (int j = 0; j < deque.size(); j++)
        {
            if (yeni_dugum->num > deque.at(index)->num)
            {
                index = j + 1;
            }
            else break;
        }

        deque.insert(deque.begin() + index, yeni_dugum);
    }

    this->root = deque.at(0);
    this->node_count = n * 2 - 1;
}

void HuffmanTree::list_preorder_private(HuffmanTree::node* node)
{
    if (node == nullptr)
        return;

    if (node->left == nullptr && node->right == nullptr)
    {
        std::cout << node->k << '*';
    }

    std::cout << node->num << ' ';
    this->list_preorder_private(node->left);
    this->list_preorder_private(node->right);
}
void HuffmanTree::list_preorder()
{
    this->list_preorder_private(this->root);
}
