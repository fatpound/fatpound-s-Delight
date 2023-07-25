#pragma once

#include "fatpound.hpp"

namespace fatpound::graph
{
    class FloydWarshall
    {
    private:
        std::vector<std::vector<std::int64_t>> result;

        graph* G = nullptr;


    protected:


    public:
        FloydWarshall(graph* graf);
        ~FloydWarshall();

        void run();
    };

    FloydWarshall::FloydWarshall(graph* graf)
    {
        this->G = graf;

        for (std::size_t i = 0; i < this->G->adj.size(); i++)
        {
            std::vector<std::int64_t> vec;

            for (std::size_t j = 0; j < this->G->adj.size(); j++)
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
                    vec.push_back(99999); // INT64_MAX
                }
            }

            this->result.push_back(vec);
        }
    }
    FloydWarshall::~FloydWarshall()
    {
        this->G->~graph();
    }

    void FloydWarshall::run()
    {
        for (std::size_t k = 0; k < this->result.size(); k++)
        {
            for (std::size_t i = 0; i < this->result.size(); i++)
            {
                for (std::size_t j = 0; j < this->result.size(); j++)
                {
                    if (this->result.at(i).at(j) > this->result.at(i).at(k) + this->result.at(k).at(j))
                        this->result.at(i).at(j) = this->result.at(i).at(k) + this->result.at(k).at(j);
                }
            }
        }

        for (std::size_t i = 0; i < this->result.size(); i++)
        {
            for (std::size_t j = 0; j < this->result.size(); j++)
                std::cout << this->result.at(i).at(j) << ' ';

            std::cout << '\n';
        }
    }
}