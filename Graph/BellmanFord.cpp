#include "BellmanFord.hpp"

namespace fatpound::graph
{
    BellmanFord::BellmanFord(BellmanFord&& src) noexcept
        :
        G{ std::move(src.G) },
        output{ std::move(src.output) }
    {}
    BellmanFord& BellmanFord::operator = (BellmanFord&& src) noexcept
    {
        G = std::move(src.G);
        output = std::move(src.output);

        return *this;
    }

    BellmanFord::BellmanFord(const std::string& input_filename, size_t source_index)
        :
        G{ std::make_unique<Graph>(input_filename) }
    {
        std::array<std::vector<std::array<size_t, 2>>, 3> edges = {};

        std::vector<int64_t> d;
        std::vector<int64_t> p;

        for (size_t i = 0; i < G->GetNodeCount(); i++)
        {
            d.push_back(std::numeric_limits<int64_t>::max()); // INT64_MAX
            p.push_back(-1);
        }

        d[source_index] = 0;

        std::vector<std::array<size_t, 2>> new_vec1 = {};
        std::vector<std::array<size_t, 2>> new_vec2 = {};
        std::vector<std::array<size_t, 2>> new_vec3 = {};

        for (size_t i = 0; i < G->GetNodeCount(); i++)
        {
            for (size_t j = 0; j < G->GetNodeAt(i)->GetNextIndexesListSize(); j++)
            {
                const size_t dest_index = G->GetNodeAt(i)->GetNextIndexesList()[j];

                if (i == source_index)
                {
                    new_vec2.push_back(std::array<size_t, 2>{i, dest_index});
                }
                else
                {
                    if (i < dest_index)
                    {
                        new_vec1.push_back(std::array<size_t, 2>{i, dest_index});
                    }
                    else
                    {
                        new_vec3.push_back(std::array<size_t, 2>{i, dest_index});
                    }
                }
            }
        }

        edges[0] = std::move(new_vec1);
        edges[1] = std::move(new_vec2);
        edges[2] = std::move(new_vec3);

        for (size_t i = 0; i < G->GetNodeCount() - 1; i++)
        {
            for (size_t j = 0; j < edges.size(); j++)
            {
                for (size_t k = 0; k < edges[j].size(); k++)
                {
                    const size_t u = edges[j][k][0];
                    const size_t v = edges[j][k][1];

                    relax(d, p, u, v);
                }
            }
        }

        for (size_t i = 0; i < edges.size(); i++)
        {
            for (size_t j = 0; j < edges[i].size(); j++)
            {
                const size_t u = edges[i][j][0];
                const size_t v = edges[i][j][1];

                int64_t w_val = w(u, v);

                if (d.at(v) > d.at(u) + w_val)
                {
                    throw std::runtime_error("The given graph is cannot be processed by Bellman-Ford Algorithm");
                    return;
                }
            }
        }

        for (size_t i = 0; i < d.size(); i++)
        {
            output += std::to_string(d[i]);
            output += ' ';
        }

        output += '\n';

        for (size_t i = 0; i < p.size(); i++)
        {
            if (p[i] > -1)
            {
                output += (char)('A' + p[i]);
            }
            else
            {
                output += 'N';
            }
        }

        output += "\n\n";
    }

    inline void BellmanFord::relax(std::vector<int64_t>& d, std::vector<int64_t>& p, const size_t u, const size_t v)
    {
        if (d.at(v) > d.at(u) + w(u, v))
        {
            d.at(v) = d.at(u) + w(u, v);
            p.at(v) = (int64_t)u;
        }
    }

    inline int64_t BellmanFord::w(const size_t u, const size_t v)
    {
        return G->GetAdjAt(u, v);
    }

    void BellmanFord::PrintResults() const
    {
        std::cout << output;
    }
}