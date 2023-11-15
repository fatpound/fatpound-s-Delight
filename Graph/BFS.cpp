#include "BFS.hpp"

#include <queue>

namespace fatpound::graph
{
    BFS::BFS(BFS&& src) noexcept
    {
        G = std::move(src.G);
        output = std::move(src.output);
    }
    BFS& BFS::operator = (BFS&& src) noexcept
    {
        G = std::move(src.G);
        output = std::move(src.output);

        return *this;
    }

    BFS::BFS(const std::string& input_filename)
        :
        G{ std::make_unique<Graph>(input_filename) }
    {
        std::vector<fatpound::color::Color> colors(G->GetNodeCount());

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

                if (colors[v] == fatpound::color::White)
                {
                    colors[v] = fatpound::color::Gray;
                    queue.push(v);
                }
            }

            colors[u] = fatpound::color::Black;

            ss << (char)('a' + u);
        }

        output = std::move(ss.str());
        output += "\n\n";
    }

    void BFS::PrintResults() const
    {
        std::cout << output;
    }
}