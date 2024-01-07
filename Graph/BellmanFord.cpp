#include "BellmanFord.hpp"

#include <array>
#include <stdexcept>

namespace fatpound::graph
{
    BellmanFord::BellmanFord(BellmanFord&& src) noexcept
        :
        graph_(std::move(src.graph_)),
        output_(std::move(src.output_))
    {

    }
    BellmanFord& BellmanFord::operator = (BellmanFord&& src) noexcept
    {
        graph_ = std::move(src.graph_);
        output_ = std::move(src.output_);

        return *this;
    }

    BellmanFord::BellmanFord(const std::string& input_filename, size_t source_index)
        :
        graph_(std::make_unique<Graph>(input_filename))
    {
        std::array<std::vector<std::array<size_t, 2>>, 3> edges = {};

        std::vector<int64_t> d;
        std::vector<int64_t> p;

        for (size_t i = 0; i < graph_->GetNodeCount(); i++)
        {
            d.push_back(std::numeric_limits<int64_t>::max()); // INT64_MAX
            p.push_back(-1);
        }

        d[source_index] = 0;

        std::vector<std::array<size_t, 2>> new_vec1 = {};
        std::vector<std::array<size_t, 2>> new_vec2 = {};
        std::vector<std::array<size_t, 2>> new_vec3 = {};

        for (size_t i = 0; i < graph_->GetNodeCount(); i++)
        {
            for (size_t j = 0; j < graph_->GetNextList(i).size(); j++)
            {
                const size_t dest_index = graph_->GetNextList(i)[j];

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

        for (size_t i = 0; i < graph_->GetNodeCount() - 1; i++)
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
                }
            }
        }

        for (size_t i = 0; i < d.size(); i++)
        {
            output_ += std::to_string(d[i]);
            output_ += ' ';
        }

        output_ += '\n';

        for (size_t i = 0; i < p.size(); i++)
        {
            if (p[i] > -1)
            {
                output_ += static_cast<char>('A' + p[i]);
            }
            else
            {
                output_ += 'N';
            }
        }

        output_ += "\n\n";
    }


    int64_t BellmanFord::w(const size_t& u, const size_t& v)
    {
        return graph_->GetAdjAt(u, v);
    }

    void BellmanFord::relax(std::vector<int64_t>& d, std::vector<int64_t>& p, const size_t& u, const size_t& v)
    {
        if (d.at(v) > d.at(u) + w(u, v))
        {
            d.at(v) = d.at(u) + w(u, v);
            p.at(v) = static_cast<int64_t>(u);
        }
    }

    void BellmanFord::PrintResults() const
    {
        std::cout << output_;
    }
}