#include "BFS.hpp"

#include <queue>

namespace fatpound::graph
{
    BFS::BFS(BFS&& src) noexcept
        :
        graph_(std::move(src.graph_)),
        output_(std::move(src.output_))
    {

    }
    BFS& BFS::operator = (BFS&& src) noexcept
    {
        graph_  = std::move(src.graph_);
        output_ = std::move(src.output_);

        return *this;
    }

    BFS::BFS(const std::string& input_filename)
        :
        graph_(std::make_unique<Graph>(input_filename))
    {
        std::vector<fatpound::util::Color> colors(graph_->GetNodeCount());

        std::queue<std::size_t> queue;
        queue.push(0);

        std::stringstream ss;

        while (queue.size() > 0)
        {
            std::size_t u = queue.front();
            queue.pop();

            for (std::size_t i = 0; i < graph_->GetNextList(u).size(); i++)
            {
                const std::size_t v = graph_->GetNextList(u)[i];

                if (colors[v] == fatpound::colors::White)
                {
                    colors[v] = fatpound::colors::Gray;
                    queue.push(v);
                }
            }

            colors[u] = fatpound::colors::Black;

            ss << static_cast<char>('a' + u);
        }

        output_  = std::move(ss.str());
        output_ += '\n';
    }


    void BFS::PrintResults() const
    {
        std::cout << output_;
    }
}