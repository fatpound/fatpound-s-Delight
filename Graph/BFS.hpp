#pragma once

#include "graph.hpp"

namespace fatpound::graph
{
    class BFS
    {
    private:
        std::queue<std::size_t> queue;
        std::vector<std::int64_t> colors;

        graph* G = nullptr;


    protected:


    public:
        BFS(graph* graf);
        ~BFS();

        void run();
    };

    BFS::BFS(graph* graf)
    {
        if (graf != nullptr)
            this->G = graf;
    }
    BFS::~BFS()
    {
        if (this->G != nullptr)
            this->G->~graph();
    }

    void BFS::run()
    {
        if (this->G == nullptr)
            return;

        for (std::size_t i = 0; i < this->G->nodes.size(); i++)
            this->colors.push_back(fatpound::graph::color_white);

        this->queue.push(0);

        while (this->queue.size() > 0)
        {
            std::size_t u = this->queue.front();
            this->queue.pop();

            for (std::size_t i = 0; i < this->G->nodes.at(u)->next_list.size(); i++)
            {
                const std::size_t v = this->G->nodes.at(u)->next_list.at(i)->n;

                if (this->colors.at(v) == fatpound::graph::color_white)
                {
                    this->colors.at(v) = fatpound::graph::color_gray;
                    this->queue.push(v);
                }
            }

            this->colors.at(u) = fatpound::graph::color_black;
            std::cout << (char)('a' + u);
        }

        std::cout << '\n';
    }
}