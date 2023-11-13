#pragma once

#include "Graph.hpp"

#include <queue>

namespace fatpound::graph
{
    class BFS
    {
    public:
        BFS() = delete;
        ~BFS() = default;
        BFS(const BFS& src) = delete;
        BFS(BFS&& src) noexcept
        {
            G = std::move(src.G);
            output = std::move(src.output);
        }
        BFS& operator = (const BFS& src) = delete;
        BFS& operator = (BFS&& src) noexcept
        {
            G = std::move(src.G);
            output = std::move(src.output);

            return *this;
        }

        BFS(const std::string& input_filename)
            :
            G{ std::make_unique<fatpound::graph::Graph>(input_filename) }
        {
            std::vector<fatpound::colors::Color> colors(G->GetNodeCount());

            std::queue<size_t> queue;
            queue.push(0ull);

            std::stringstream ss;

            while (queue.size() > 0ull)
            {
                size_t u = queue.front();
                queue.pop();

                for (size_t i = 0; i < G->GetNodeAt(u)->next.size(); i++)
                {
                    const size_t v = G->GetNodeAt(u)->next[i];

                    if (colors[v] == fatpound::colors::White)
                    {
                        colors[v] = fatpound::colors::Gray;
                        queue.push(v);
                    }
                }

                colors[u] = fatpound::colors::Black;

                ss << (char)('a' + u);
            }

            output = std::move(ss.str());
            output += "\n\n";
        }

        void PrintResults() const
        {
            std::cout << output;
        }


    protected:


    private:
        std::unique_ptr<Graph> G = nullptr;

        std::string output;
    };
}