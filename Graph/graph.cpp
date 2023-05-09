#include "graph.h"

graph::node::node()
{

}
graph::node::~node()
{

}

void graph::node::list_all_adj()
{
    for (int i = 0; i < this->next_list.size(); i++)
    {
        std::cout << this->next_list.at(i) << "\t" << this->next_list.at(i)->n << '\n';
    }
}

graph::graph()
{

}
graph::~graph()
{

}
graph::graph(std::vector<std::vector<int>> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        std::vector<int> x;

        for (int j = 0; j < vec.size(); j++)
        {
            x.push_back(vec.at(i).at(j));
        }

        this->adj.push_back(x);
    }

    for (int i = 0; i < vec.size(); i++)
    {
        this->nodes.push_back(new node());
        this->nodes.at(i)->n = i;
    }

    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = 0; j < vec.size(); j++)
        {
            if (vec.at(i).at(j) != 0)
            {
                this->nodes.at(i)->next_list.push_back(this->nodes.at(j));
                this->edge_count++;
            }
        }
    }
}

void graph::list_nodes()
{
    for (int i = 0; i < this->nodes.size(); i++)
    {
        std::cout << this->nodes.at(i) << "\t" << this->nodes.at(i)->n << "\tsource\n";
        this->nodes.at(i)->list_all_adj();
        std::cout << "----------------" << '\n';
    }

    std::cout << '\n';
}