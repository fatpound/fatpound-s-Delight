#pragma once

#include "graph.hpp"

namespace fatpound::graph
{
    class BFS
    {
    private:
        std::queue<std::size_t> queue;
        std::vector<std::size_t> colors;

        graph* G = nullptr;

        static constexpr std::int64_t color_white = 0;
        static constexpr std::int64_t color_gray  = 1;
        static constexpr std::int64_t color_black = 2;


    protected:


    public:
        BFS(graph* graf);

        void run();
    };

    BFS::BFS(graph* graf)
    {
        this->G = graf;
    }

    void BFS::run()
    {
        if (this->G == nullptr)
            return;

        for (std::size_t i = 0; i < this->G->nodes.size(); i++)
            this->colors.push_back(color_white);

        this->queue.push(0);

        while (this->queue.size() > 0)
        {
            std::size_t u = this->queue.front();
            this->queue.pop();

            for (std::size_t i = 0; i < this->G->nodes.at(u)->next_list.size(); i++)
            {
                const std::size_t v = this->G->nodes.at(u)->next_list.at(i)->n;

                if (this->colors.at(v) == color_white)
                {
                    this->colors.at(v) = color_gray;
                    this->queue.push(v);
                }
            }

            this->colors.at(u) = color_black;
            std::cout << (char)('a' + u);
        }

        std::cout << '\n';
    }
}