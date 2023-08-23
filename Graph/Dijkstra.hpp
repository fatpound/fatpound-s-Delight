#pragma once

#include "graph.hpp"

namespace fatpound::graph
{
    class Dijkstra
    {
    private:
        std::deque<std::int64_t> deque;

        std::vector<std::int64_t> d;
        std::vector<std::int64_t> p;

        graph* G = nullptr;

        std::size_t item_count = 0;

        std::int64_t w(const std::size_t u, const std::size_t v);

        void relax(const std::size_t u, const std::size_t v);


    protected:


    public:
        Dijkstra(graph* graf, std::size_t source_index);
        ~Dijkstra();

        void run();
    };


    Dijkstra::Dijkstra(graph* graf, std::size_t source_index)
    {
        if (graf == nullptr)
            return;

        this->G = graf;

        for (std::size_t i = 0; i < graf->nodes.size(); i++)
        {
            this->d.push_back(99999); // INT32_MAX
            this->p.push_back(-1);

            this->deque.push_back((std::int64_t)i);
            this->item_count++;
        }

        this->d.at(source_index) = 0;
    }
    Dijkstra::~Dijkstra()
    {
        if (this->G != nullptr)
            this->G->~graph();
    }

    std::int64_t Dijkstra::w(const std::size_t u, const std::size_t v)
    {
        return this->G->adj.at(u).at(v);
    }

    void Dijkstra::relax(const std::size_t u, const std::size_t v)
    {
        if (this->d.at(v) > this->d.at(u) + this->w(u, v))
        {
            this->d.at(v) = this->d.at(u) + this->w(u, v);
            this->p.at(v) = (std::int64_t)u;
        }
    }
    void Dijkstra::run()
    {
        if (this->G == nullptr)
            return;

        while (this->item_count > 0)
        {
            std::size_t min_index = 0;

            bool flag = true; // does min_index need to be initialized ?

            for (std::size_t i = 0; i < this->d.size(); i++)
            {
                if (this->deque.at(i) >= 0)
                {
                    if (flag)
                    {
                        min_index = i;
                        flag = false;
                    }

                    if (this->d.at(min_index) > this->d.at(i))
                        min_index = i;
                }
            }

            const std::size_t u = (std::size_t)this->deque.at(min_index);

            this->deque.at(min_index) = -1;
            this->item_count--;

            for (std::size_t i = 0; i < this->G->nodes.at(u)->next_list.size(); i++)
                this->relax(u, this->G->nodes.at(u)->next_list.at(i)->n);
        }

        for (std::size_t i = 0; i < this->d.size(); i++)
            std::cout << this->d.at(i) << ' ';

        std::cout << '\n';

        for (std::size_t i = 0; i < this->p.size(); i++)
        {
            if (this->p.at(i) > -1)
                std::cout << (char)('A' + this->p.at(i));
            else
                std::cout << 'N';
        }

        std::cout << "\n\n";
    }
}