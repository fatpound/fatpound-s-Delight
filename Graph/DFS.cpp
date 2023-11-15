#include "DFS.hpp"

namespace fatpound::graph
{
    DFS::DFS(DFS&& src) noexcept
    {
        G = std::move(src.G);
        output = std::move(src.output);
    }
    DFS& DFS::operator = (DFS&& src) noexcept
    {
        G = std::move(src.G);
        output = std::move(src.output);

        return *this;
    }

    DFS::DFS(const std::string& input_filename)
        :
        G{ std::make_unique<Graph>(input_filename) }
    {
        std::vector<fatpound::color::Color> colors(G->GetNodeCount());

        for (size_t i = 0; i < G->GetNodeCount(); i++)
        {
            if (colors[i] == fatpound::color::White)
            {
                Visit(colors, i);
            }
        }

        output += '\n';
    }
    
    void DFS::Visit(std::vector<fatpound::color::Color>& colors, const size_t index)
    {
        colors[index] = fatpound::color::Gray;

        {
            std::stringstream ss;

            ss << G->GetNodeAt(index) << '\t' << G->GetNodeAt(index)->n << '\n';

            output += std::move(ss.str());
        }

        for (size_t i = 0; i < G->GetNodeAt(index)->next.size(); i++)
        {
            const size_t next_index = G->GetNodeAt(index)->next[i];

            if (colors[next_index] == fatpound::color::White)
            {
                Visit(colors, next_index);
            }
        }

        colors[index] = fatpound::color::Black;
    }

    void DFS::PrintResults() const
    {
        std::cout << output;
    }
}