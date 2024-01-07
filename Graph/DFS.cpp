#include "DFS.hpp"

namespace fatpound::graph
{
    DFS::DFS(DFS&& src) noexcept
    {
        graph_ = std::move(src.graph_);
        output_ = std::move(src.output_);
    }
    DFS& DFS::operator = (DFS&& src) noexcept
    {
        graph_ = std::move(src.graph_);
        output_ = std::move(src.output_);

        return *this;
    }

    DFS::DFS(const std::string& input_filename)
        :
        graph_(std::make_unique<Graph>(input_filename))
    {
        std::vector<fatpound::color::Color> colors(graph_->GetNodeCount());

        for (size_t i = 0u; i < graph_->GetNodeCount(); ++i)
        {
            if (colors[i] == fatpound::color::White)
            {
                Visit(colors, i);
            }
        }

        output_ += '\n';
    }
    
    void DFS::Visit(std::vector<fatpound::color::Color>& colors, const size_t& index)
    {
        colors[index] = fatpound::color::Gray;

        std::stringstream ss;
        
        ss << index << '\n';

        output_ += std::move(ss.str());

        for (size_t i = 0; i < graph_->GetNextList(index).size(); ++i)
        {
            const size_t nextIndex = graph_->GetNextList(index)[i];

            if (colors[nextIndex] == fatpound::color::White)
            {
                Visit(colors, nextIndex);
            }
        }

        colors[index] = fatpound::color::Black;
    }
    void DFS::PrintResults() const
    {
        std::cout << output_;
    }
}