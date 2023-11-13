#pragma once

#include "Graph.hpp"

#include <sstream>
#include <vector>
#include <string>
#include <memory>

namespace fatpound::graph
{
    class DFS
    {
    public:
        DFS() = delete;
        ~DFS() = default;
        DFS(const DFS& src) = delete;
        DFS(DFS&& src) noexcept
        {
            G = std::move(src.G);
            output = std::move(src.output);
        }
        DFS& operator = (const DFS& src) = delete;
        DFS& operator = (DFS&& src) noexcept
        {
            G = std::move(src.G);
            output = std::move(src.output);

            return *this;
        }

        DFS(const std::string& input_filename)
            :
            G{ std::make_unique<fatpound::graph::Graph>(input_filename) }
        {
            std::vector<fatpound::colors::Color> colors(G->GetNodeCount());

            for (size_t i = 0; i < G->GetNodeCount(); i++)
            {
                if (colors[i] == fatpound::colors::White)
                {
                    Visit(colors, i);
                }
            }

            output += '\n';
        }

        void PrintResults() const
        {
            std::cout << output;
        }


    protected:


    private:
        std::unique_ptr<Graph> G = nullptr;

        std::string output;

        void Visit(std::vector<fatpound::colors::Color>& colors, const size_t index)
        {
            colors[index] = fatpound::colors::Gray;

            {
                std::stringstream ss;

                ss << G->GetNodeAt(index) << '\t' << G->GetNodeAt(index)->n << '\n';

                output += std::move(ss.str());
            }

            for (size_t i = 0; i < G->GetNodeAt(index)->next.size(); i++)
            {
                const size_t next_index = G->GetNodeAt(index)->next[i];

                if (colors[next_index] == fatpound::colors::White)
                {
                    Visit(colors, next_index);
                }
            }

            colors[index] = fatpound::colors::Black;
        }
    };
}