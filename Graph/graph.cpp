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
        cout << this->next_list.at(i) << "\t" << this->next_list.at(i)->n << '\n';
    }
}

graph::graph()
{

}
graph::~graph()
{

}
graph::graph(vector<vector<int>> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        vector<int> x;

        for (int j = 0; j < vec.size(); j++)
        {
            x.push_back(vec.at(i).at(j));
        }

        this->adj.push_back(x);
    }

    for (int i = 0; i < vec.size(); i++)
    {
        this->all_nodes.push_back(new node());
        this->all_nodes.at(i)->n = i;
    }

    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = 0; j < vec.size(); j++)
        {
            if (vec.at(i).at(j) != 0)
            {
                this->all_nodes.at(i)->next_list.push_back(this->all_nodes.at(j));
            }
        }
    }
}

void graph::list_all_nodes()
{
    for (int i = 0; i < this->all_nodes.size(); i++)
    {
        cout << this->all_nodes.at(i) << "\t" << this->all_nodes.at(i)->n << "\tsource\n";
        this->all_nodes.at(i)->list_all_adj();
        cout << "----------------" << '\n';
    }

    cout << '\n';
}