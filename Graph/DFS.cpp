#include "DFS.h"

int DFS::color_white = 0;
int DFS::color_gray = 1;
int DFS::color_black = 2;

DFS::DFS()
{

}
DFS::~DFS()
{

}
DFS::DFS(graph* graf)
{
    this->G = graf;

    for (int i = 0; i < this->G->nodes.size(); i++)
    {
        this->colors.push_back(color_white);
    }
}

void DFS::visit(int index)
{
    this->colors.at(index) = color_gray;

    std::cout << this->G->nodes.at(index) << '\t' << this->G->nodes.at(index)->n << '\n';

    for (int i = 0; i < this->G->nodes.at(index)->next_list.size(); i++)
    {
        int next_index = this->G->nodes.at(index)->next_list.at(i)->n;

        if (this->colors.at(next_index) == color_white)
        {
            this->visit(next_index);
        }
    }

    this->colors.at(index) = color_black;
}
void DFS::run()
{
    for (int i = 0; i < this->G->nodes.size(); i++)
    {
        if (this->colors.at(i) == color_white)
        {
            this->visit(i);
        }
    }
}