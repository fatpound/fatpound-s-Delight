#include "Dijkstra.hpp"

#include <deque>

namespace fatpound::dsa::graph
{
    Dijkstra::Dijkstra(Dijkstra&& src) noexcept
        :
        graph_(std::move(src.graph_)),
        output_(std::move(src.output_))
    {

    }
    Dijkstra& Dijkstra::operator = (Dijkstra&& src) noexcept
    {
        graph_  = std::move(src.graph_);
        output_ = std::move(src.output_);
        
        return *this;
    }

    Dijkstra::Dijkstra(const std::string& input_filename, std::size_t source_index)
        :
        graph_(std::make_unique<Graph>(input_filename))
    {
        std::deque<std::int64_t> deque;

        std::vector<std::int64_t> d;
        std::vector<std::int64_t> p;

        for (std::size_t i = 0; i < graph_->GetNodeCount(); i++)
        {
            d.push_back(std::numeric_limits<std::int64_t>::max());
            p.push_back(-1);

            deque.push_back((std::int64_t)i);
        }

        std::size_t item_count = graph_->GetNodeCount();

        d[source_index] = 0;

        while (item_count > 0)
        {
            std::size_t min_index = 0;

            bool flag = true; // does min_index need to be initialized ?

            for (std::size_t i = 0; i < d.size(); i++)
            {
                if (deque[i] >= 0)
                {
                    if (flag)
                    {
                        min_index = i;
                        flag = false;
                    }

                    if (d[min_index] > d[i])
                    {
                        min_index = i;
                    }
                }
            }

            const std::size_t u = static_cast<std::size_t>(deque[min_index]);

            deque[min_index] = -1;
            item_count--;

            auto& nextindexes = graph_->GetNextList(u);

            for (std::size_t i = 0; i < nextindexes.size(); i++)
            {
                relax_(d, p, u, nextindexes[i]);
            }
        }

        for (std::size_t i = 0; i < d.size(); i++)
        {
            output_ += std::to_string(d[i]) + ' ';
        }

        output_ += '\n';

        for (std::size_t i = 0; i < p.size(); i++)
        {
            if (p[i] > -1)
            {
                output_ += static_cast<char>('A' + p[i]);
                output_ += ' ';
            }
            else
            {
                output_ += "N ";
            }
        }

        output_ += "\n\n";
    }


    std::int64_t Dijkstra::w_(const std::size_t& u, const std::size_t& v) const
    {
        return graph_->GetAdjAt(u, v);
    }

    void Dijkstra::relax_(std::vector<std::int64_t>& d, std::vector<std::int64_t>& p, const std::size_t& u, const std::size_t& v)
    {
        if (d[v] > d[u] + w_(u, v))
        {
            d[v] = d[u] + w_(u, v);
            p[v] = static_cast<std::int64_t>(u);
        }
    }

    void Dijkstra::PrintResults() const
    {
        std::cout << output_;
    }
}