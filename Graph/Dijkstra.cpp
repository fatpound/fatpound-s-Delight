#include "Dijkstra.hpp"

#include <deque>

namespace fatpound::graph
{
    Dijkstra::Dijkstra(Dijkstra&& src) noexcept
        :
        G{ std::move(src.G) },
        output{ std::move(src.output) }
    {}
    Dijkstra& Dijkstra::operator = (Dijkstra && src) noexcept
    {
        G = std::move(src.G);
        output = std::move(src.output);

        return *this;
    }

    Dijkstra::Dijkstra(const std::string& input_filename, size_t source_index)
        :
        G{ std::make_unique<Graph>(input_filename) }
    {
        std::deque<int64_t> deque;
        std::vector<int64_t> d;
        std::vector<int64_t> p;

        for (size_t i = 0; i < G->GetNodeCount(); i++)
        {
            d.push_back(std::numeric_limits<int64_t>::max());
            p.push_back(-1);

            deque.push_back((int64_t)i);
        }

        size_t item_count = G->GetNodeCount();

        d[source_index] = 0;

        while (item_count > 0)
        {
            size_t min_index = 0;

            bool flag = true; // does min_index need to be initialized ?

            for (size_t i = 0; i < d.size(); i++)
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

            const size_t u = (size_t)deque[min_index];

            deque[min_index] = -1;
            item_count--;

            auto& nextindexes = G->GetNodeAt(u)->GetNextIndexesList();

            for (size_t i = 0; i < nextindexes.size(); i++)
            {
                relax(d, p, u, nextindexes[i]);
            }
        }

        for (size_t i = 0; i < d.size(); i++)
        {
            output += std::to_string(d[i]) + ' ';
        }

        output += '\n';

        for (size_t i = 0; i < p.size(); i++)
        {
            if (p[i] > -1)
            {
                output += (char)('A' + p[i]);
                output += ' ';
            }
            else
            {
                output += "N ";
            }
        }

        output += "\n\n";
    }

    void Dijkstra::PrintResults() const
    {
        std::cout << output;
    }

    inline void Dijkstra::relax(std::vector<int64_t>& d, std::vector<int64_t>& p, const size_t u, const size_t v)
    {
        if (d[v] > d[u] + w(u, v))
        {
            d[v] = d[u] + w(u, v);
            p[v] = (int64_t)u;
        }
    }

    inline int64_t Dijkstra::w(const size_t u, const size_t v) const
    {
        return G->GetAdjAt(u, v);
    }
}