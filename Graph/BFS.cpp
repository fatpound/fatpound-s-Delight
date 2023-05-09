#include "BFS.h"

int BFS::color_white = 0;
int BFS::color_gray = 1;
int BFS::color_black = 2;

BFS::BFS()
{

}
BFS::~BFS()
{

}
BFS::BFS(graph* graf)
{
    this->G = graf;
}

void BFS::run()
{
    for (int i = 0; i < this->G->nodes.size(); i++)
    {
        this->colors.push_back(color_white);
    }

    this->queue.push(0);

    while (this->queue.size() > 0)
    {
        int u = this->queue.front();
        this->queue.pop();

        for (int i = 0; i < this->G->nodes.at(u)->next_list.size(); i++)
        {
            int v = this->G->nodes.at(u)->next_list.at(i)->n;

            if (this->colors.at(v) == color_white)
            {
                this->colors.at(v) = color_gray;
                this->queue.push(v);
            }
        }

        this->colors.at(u) = color_black;
        std::cout << "abcdefghi"[u];
    }

    std::cout << '\n';
}