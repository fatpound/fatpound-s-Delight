#include "DFS.hpp"

namespace fatpound::graph
{
    DFS::DFS(DFS&& src) noexcept
        :
        graph_(std::move(src.graph_)),
        output_(std::move(src.output_))
    {
        
    }
    DFS& DFS::operator = (DFS&& src) noexcept
    {
        graph_  = std::move(src.graph_);
        output_ = std::move(src.output_);

        return *this;
    }

    DFS::DFS(const std::string& input_filename)
        :
        graph_(std::make_unique<Graph>(input_filename))
    {
        std::vector<fatpound::util::Color> colors(graph_->GetNodeCount());

        for (std::size_t i = 0u; i < graph_->GetNodeCount(); ++i)
        {
            if (colors[i] == fatpound::colors::White)
            {
                Visit_(colors, i);
            }
        }

        output_ += '\n';
    }
    

    void DFS::Visit_(std::vector<fatpound::util::Color>& colors, const std::size_t& index)
    {
        colors[index] = fatpound::colors::Gray;

        std::stringstream ss;
        
        ss << index << '\n';

        output_ += std::move(ss.str());

        for (std::size_t i = 0; i < graph_->GetNextList(index).size(); ++i)
        {
            const std::size_t nextIndex = graph_->GetNextList(index)[i];

            if (colors[nextIndex] == fatpound::colors::White)
            {
                Visit_(colors, nextIndex);
            }
        }

        colors[index] = fatpound::colors::Black;
    }
    void DFS::PrintResults() const
    {
        std::cout << output_;
    }
}