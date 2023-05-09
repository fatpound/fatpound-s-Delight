#include "Dijkstra.h"

int Dijkstra::w(int u, int v)
{
    return this->G->adj.at(u).at(v);
}

void Dijkstra::relax(int u, int v)
{
    if (this->d.at(v) > this->d.at(u) + this->w(u, v))
    {
        this->d.at(v) = this->d.at(u) + this->w(u, v);
        this->p.at(v) = u;
    }
}

Dijkstra::Dijkstra()
{
    
}
Dijkstra::~Dijkstra()
{

}
Dijkstra::Dijkstra(graph* graf, int source_index)
{
    this->G = graf;

    for (int i = 0; i < graf->nodes.size(); i++)
    {
        this->d.push_back(999); // INT32_MAX
        this->p.push_back(-1);

        this->deque.push_back(i);
        this->item_count++;
    }

    this->d.at(source_index) = 0;
}

void Dijkstra::run()
{
    while (this->item_count > 0)
    {
        int min_index = -1;

        for (int i = 0; i < this->d.size(); i++)
        {
            if (this->deque.at(i) >= 0)
            {
                if (min_index == -1)
                    min_index = i;

                if (this->d.at(min_index) > this->d.at(i))
                {
                    min_index = i;
                }
            }
        }

        int u = this->deque.at(min_index);
        this->deque.at(min_index) = -1;
        this->item_count--;

        for (int i = 0; i < this->G->nodes.at(u)->next_list.size(); i++)
        {
            this->relax(u, this->G->nodes.at(u)->next_list.at(i)->n);
        }
    }

    for (int i = 0; i < this->d.size(); i++)
    {
        std::cout << this->d.at(i) << ' ';
    }

    std::cout << '\n';

    for (int i = 0; i < this->p.size(); i++)
    {
        if (this->p.at(i) > -1)
        {
            std::cout << "ABCDEFGHI"[this->p.at(i)];
        }
        else
            std::cout << "N";
    }

    std::cout << "\n\n";
}