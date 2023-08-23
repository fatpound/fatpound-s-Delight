#pragma once

#include "graph.hpp"

namespace fatpound::graph
{
    class DFS
    {
    private:
        std::vector<std::int64_t> colors;
        
        graph* G = nullptr;

        void visit(const std::size_t index);


    protected:


    public:
        DFS(graph* graf);
        ~DFS();

        void run();
    };

    DFS::DFS(graph* graf)
    {
        this->G = graf;

        for (std::size_t i = 0; i < this->G->nodes.size(); i++)
            this->colors.push_back(fatpound::graph::color_white);
    }
    DFS::~DFS()
    {
        this->G->~graph();
    }

    void DFS::visit(const std::size_t index)
    {
        this->colors.at(index) = fatpound::graph::color_gray;

        std::cout << this->G->nodes.at(index) << '\t' << this->G->nodes.at(index)->n << '\n';

        for (std::size_t i = 0; i < this->G->nodes.at(index)->next_list.size(); i++)
        {
            const std::size_t next_index = this->G->nodes.at(index)->next_list.at(i)->n;

            if (this->colors.at(next_index) == fatpound::graph::color_white)
                this->visit(next_index);
        }

        this->colors.at(index) = fatpound::graph::color_black;
    }
    void DFS::run()
    {
        if (this->G == nullptr)
            return;

        for (std::size_t i = 0; i < this->G->nodes.size(); i++)
        {
            if (this->colors.at(i) == fatpound::graph::color_white)
                this->visit(i);
        }
    }
}