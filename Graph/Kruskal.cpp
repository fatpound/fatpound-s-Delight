#include "Kruskal.hpp"

#include <vector>
#include <array>
#include <algorithm>
#include <ranges>

namespace rn = std::ranges;

namespace fatpound::graph
{
    Kruskal::Kruskal(Kruskal&& src) noexcept
        :
        graph_(std::move(src.graph_))
    {

    }
    Kruskal& Kruskal::operator = (Kruskal&& src) noexcept
    {
        graph_ = std::move(src.graph_);

        return *this;
    }

    Kruskal::Kruskal(const std::string& input_filename)
        :
        graph_(std::make_unique<Graph>(input_filename))
    { 
        std::vector<std::int64_t> weighs;
        std::vector<std::int64_t> weighs_counts;

        std::int64_t last = -1;

        const std::int64_t nodeCount = graph_->GetNodeCount();

        //////////////
        // Set different weighs

        for (std::int64_t i = 0; i < nodeCount; ++i)
        {
            for (std::int64_t j = 0; j < nodeCount; ++j)
            {
                std::int64_t n = graph_->GetAdjAt(i, j);

                if (n != 0 && !rn::any_of(weighs, [&](const auto& num) {return num == n;}))
                {
                    weighs.push_back(n);
                    weighs_counts.push_back(0);
                }
            }
        }

        rn::sort(weighs);

        std::vector<std::vector<std::vector<std::int64_t>>> edges;
        edges.resize(weighs.size());

        for (std::int64_t i = 0; i < nodeCount; ++i)
        {
            for (std::int64_t j = 0; j < nodeCount; ++j)
            {
                const std::int64_t n = graph_->GetAdjAt(i, j);

                if (n != 0 && IsNotInEdges_(weighs, edges, n, i, j))
                {
                    const std::size_t index = rn::find(weighs, n) - weighs.cbegin();

                    ++weighs_counts[index];

                    edges[index].push_back(std::vector<std::int64_t>{ i, j });
                }
            }
        }

        for (std::int64_t i = 0; i < static_cast<std::int64_t>(weighs_counts.size()); ++i)
        {
            weighs_counts[i] /= 2;
        }

        //////////////

        std::vector<std::vector<std::int64_t>> result;
        result.resize(graph_->GetEdgeCount());

        for (std::int64_t i = 0; i < static_cast<std::int64_t>(result.size()); ++i)
        {
            result[i].push_back(i);
        }

        for (std::int64_t i = 0; i < static_cast<std::int64_t>(edges.size()); ++i)
        {
            for (std::int64_t j = 0; j < static_cast<std::int64_t>(edges[i].size()); ++j)
            {
                if (AvailableInResult_(result, edges[i][j]))
                {
                    SetResult_(result, edges[i][j], last);
                }
            }
        }

        for (std::int64_t i = 0; i < static_cast<std::int64_t>(result[last].size()); ++i)
        {
            output_ += "abcdefghijk"[result[last][i]];
        }

        output_ += '\n';
    }


    std::int64_t Kruskal::GetIndexFromResult_(std::vector<std::vector<std::int64_t>>& result, const std::int64_t& value)
    {
        for (std::size_t i = 0; i < result.size(); ++i)
        {
            for (std::size_t j = 0; j < result[i].size(); ++j)
            {
                if (result[i][j] == value)
                {
                    return static_cast<std::int64_t>(i);
                }
            }
        }

        return -1;
    }

    bool Kruskal::IsNotInEdges_(std::vector<std::int64_t>& weighs, std::vector<std::vector<std::vector<std::int64_t>>>& edges, std::int64_t n, std::int64_t x, std::int64_t y)
    {
        std::int64_t index = std::find(weighs.cbegin(), weighs.cend(), n) - weighs.cbegin();

        for (std::int64_t j = 0; j < static_cast<std::int64_t>(edges[index].size()); ++j)
        {
            std::array<std::int64_t, 2> arr = { 0, 0 };

            for (std::int64_t k = 0; k < static_cast<std::int64_t>(edges[index][j].size()); k++)
            {
                std::int64_t n = edges[index][j][k];

                if (n == x)
                {
                    arr[0]++;
                }
                else if (n == y)
                {
                    arr[1]++;
                }

                if (arr[0] > 0 && arr[1] > 0)
                {
                    return false;
                }
            }
        }

        return true;
    }
    bool Kruskal::AvailableInResult_(std::vector<std::vector<std::int64_t>>& result, std::vector<std::int64_t>& vec)
    {
        for (std::size_t i = 0; i < result.size(); ++i)
        {
            if (vec.size() <= result[i].size())
            {
                std::array<std::int64_t, 2> arr = { 0, 0 };

                for (std::size_t j = 0; j < result[i].size(); ++j)
                {
                    std::int64_t n = result[i][j];

                    if (n == vec[0])
                    {
                        arr[0]++;
                    }
                    else if (n == vec[1])
                    {
                        arr[1]++;
                    }

                    if (arr[0] > 0 && arr[1] > 0)
                    {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    void Kruskal::SetResult_(std::vector<std::vector<std::int64_t>>& result, std::vector<std::int64_t>& vec, std::int64_t& last)
    {
        std::int64_t index_1 = GetIndexFromResult_(result, vec[0]); // index of 'g'
        std::int64_t index_2 = GetIndexFromResult_(result, vec[1]); // index of 'h'

        if (index_1 < 0 || index_2 < 0)
        {
            return;
        }

        if (result[index_1].size() >= result[index_2].size())
        {
            for (std::size_t k = 0; k < result[index_2].size(); k++)
            {
                result[index_1].push_back(result[index_2][k]);
                result[index_2][k] = -1; // erasing
            }

            last = index_1;
            return;
        }

        if (result[index_2].size() >= result[index_1].size())
        {
            for (std::size_t k = 0; k < result[index_1].size(); k++)
            {
                result[index_2].push_back(result[index_1][k]);
                result[index_1][k] = -1; // erasing
            }

            last = index_2;
            return;
        }
    }

    void Kruskal::PrintResults() const
    {
        std::cout << output_;
    }
}