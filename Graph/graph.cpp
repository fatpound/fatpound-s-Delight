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
graph::graph(std::string str)
{
    graph_reader gr(str);

    this->adj = std::vector<std::vector<int>>(gr.adj_matrix);
    this->node_count = this->adj.size();

    for (int i = 0; i < this->adj.size(); i++)
    {
        this->nodes.push_back(new node());
        this->nodes.at(i)->n = i;
    }

    for (int i = 0; i < this->adj.size(); i++)
    {
        for (int j = 0; j < this->adj.size(); j++)
        {
            if (this->adj.at(i).at(j) != 0)
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