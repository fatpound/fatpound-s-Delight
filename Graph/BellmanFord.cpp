#include "BellmanFord.h"

int BellmanFord::w(int u, int v)
{
    return this->G->adj.at(u).at(v);
}

void BellmanFord::relax(int u, int v)
{
    if (this->d.at(v) > this->d.at(u) + this->w(u, v))
    {
        this->d.at(v) = this->d.at(u) + this->w(u, v);
        this->p.at(v) = u;
    }
}

BellmanFord::BellmanFord()
{

}
BellmanFord::~BellmanFord()
{

}
BellmanFord::BellmanFord(graph* graf, int source_index)
{
    this->G = graf;

    for (int i = 0; i < graf->all_nodes.size(); i++)
    {
        this->d.push_back(999); // INT32_MAX
        this->p.push_back(-1);
    }

    this->d.at(source_index) = 0;

    vector<array<int, 2>> new_vec1;
    vector<array<int, 2>> new_vec2;
    vector<array<int, 2>> new_vec3;

    for (int i = 0; i < this->G->all_nodes.size(); i++)
    {
        for (int j = 0; j < this->G->all_nodes.at(i)->next_list.size(); j++)
        {
            int dest_index = this->G->all_nodes.at(i)->next_list.at(j)->n;

            array<int, 2> new_edge;

            new_edge.at(0) = i;
            new_edge.at(1) = dest_index;

            if (i == source_index)
            {
                new_vec2.push_back(new_edge);
            }
            else
            {
                if (i < dest_index)
                {
                    new_vec1.push_back(new_edge);
                }
                else
                {
                    new_vec3.push_back(new_edge);
                }
            }
        }
    }

    this->edges.at(0) = new_vec1;
    this->edges.at(1) = new_vec2;
    this->edges.at(2) = new_vec3;
}

bool BellmanFord::run()
{
    for (int i = 0; i < this->G->all_nodes.size() - 1; i++)
    {
        for (int j = 0; j < this->edges.size(); j++)
        {
            for (int k = 0; k < this->edges.at(j).size(); k++)
            {
                int u = this->edges.at(j).at(k).at(0);
                int v = this->edges.at(j).at(k).at(1);

                this->relax(u, v);
            }
        }
    }

    for (int i = 0; i < this->edges.size(); i++)
    {
        for (int j = 0; j < this->edges.at(i).size(); j++)
        {
            int u = this->edges.at(i).at(j).at(0);
            int v = this->edges.at(i).at(j).at(1);

            int w_val = this->w(u, v);

            if (this->d.at(v) > this->d.at(u) + w_val)
            {
                return false;
            }
        }
    }

    // RESULTS
    for (int x = 0; x < this->d.size(); x++)
    {
        cout << this->d.at(x) << ' ';
    }

    cout << '\n';

    for (int x = 0; x < this->p.size(); x++)
    {
        if (this->p.at(x) > -1)
        {
            cout << "ABCDEFGHI"[this->p.at(x)];
        }
        else
            cout << "N";
    }

    cout << "\n\n";

    return true;
}