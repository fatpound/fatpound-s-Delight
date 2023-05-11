#include "FloydWarshall.h"

FloydWarshall::FloydWarshall()
{

}
FloydWarshall::~FloydWarshall()
{

}
FloydWarshall::FloydWarshall(graph* graf)
{
    this->G = graf;

    for (int i = 0; i < this->G->adj.size(); i++)
    {
        std::vector<int> vec;

        for (int j = 0; j < this->G->adj.size(); j++)
        {
            if (i == j)
            {
                vec.push_back(0);
            }
            else if (graf->adj.at(i).at(j) != 0)
            {
                vec.push_back(graf->adj.at(i).at(j));
            }
            else
            {
                vec.push_back(999); // INT32_MAX
            }
        }

        this->result.push_back(vec);
    }
}

void FloydWarshall::run()
{
    for (int k = 0; k < this->result.size(); k++)
    {
        for (int i = 0; i < this->result.size(); i++)
        {
            for (int j = 0; j < this->result.size(); j++)
            {
                if (this->result.at(i).at(j) > this->result.at(i).at(k) + this->result.at(k).at(j))
                    this->result.at(i).at(j) = this->result.at(i).at(k) + this->result.at(k).at(j);
            }
        }
    }

    for (int i = 0; i < this->result.size(); i++)
    {
        for (int j = 0; j < this->result.size(); j++)
        {
            std::cout << this->result.at(i).at(j) << ' ';
        }

        std::cout << '\n';
    }
}