#include "Kruskal.hpp"

#include <algorithm>

namespace fatpound::graph
{
    Kruskal::Kruskal(Kruskal&& src) noexcept
        :
        G{ std::move(src.G) }
    {}
    Kruskal& Kruskal::operator = (Kruskal&& src) noexcept
    {
        G = std::move(src.G);

        return *this;
    }

    Kruskal::Kruskal(const std::string& input_filename)
        :
        G{ std::make_unique<Graph>(input_filename) }
    {
        std::vector<int64_t> weighs;
        std::vector<int64_t> weighs_counts;
        std::vector<std::vector<int64_t>> result;
        std::vector<std::vector<std::vector<int64_t>>> edges;

        int64_t last = -1;

        //////////////
        // Set different weighs

        for (int64_t i = 0; i < G->GetNodeCount(); i++)
        {
            for (int64_t j = 0; j < G->GetNodeCount(); j++)
            {
                int64_t n = G->GetAdjAt(i, j);

                if (n != 0 && !std::any_of(weighs.cbegin(), weighs.cend(), [&](auto& num) {return num == n;}))
                {
                    weighs.push_back(n);
                    weighs_counts.push_back(0);
                }
            }
        }

        std::sort(weighs.begin(), weighs.end());
        edges.resize(weighs.size());

        for (int64_t i = 0; i < G->GetNodeCount(); i++)
        {
            for (int64_t j = 0; j < G->GetNodeCount(); j++)
            {
                int64_t n = G->GetAdjAt(i, j);

                if (n != 0 && IsNotInEdges(weighs, edges, n, i, j))
                {
                    const size_t index = std::find(weighs.cbegin(), weighs.cend(), n) - weighs.cbegin();

                    weighs_counts[index]++;

                    edges[index].push_back(std::vector<int64_t>{ i, j });
                }
            }
        }

        for (int64_t i = 0; i < weighs_counts.size(); i++)
        {
            weighs_counts[i] /= 2;
        }

        //////////////

        result.resize(G->GetEdgeCount());

        for (int64_t i = 0; i < result.size(); i++)
        {
            result[i] = std::vector<int64_t>{i};
        }

        for (int64_t i = 0; i < edges.size(); i++)
        {
            for (int64_t j = 0; j < edges[i].size(); j++)
            {
                if (AvailableInResult(result, edges[i][j]))
                {
                    SetResult(result, edges[i][j], last);
                }
            }
        }
        for (int64_t i = 0; i < result[last].size(); i++)
        {
            std::cout << "abcdefghijk"[result[last][i]];
        }

        std::cout << '\n';
    }

    int64_t Kruskal::GetIndexFromResult(std::vector<std::vector<int64_t>>& result, int64_t value)
    {
        for (int64_t i = 0; i < result.size(); i++)
        {
            for (int64_t j = 0; j < result[i].size(); j++)
            {
                if (result[i][j] == value)
                {
                    return i;
                }
            }
        }

        return -1;
    }

    bool Kruskal::IsNotInEdges(std::vector<int64_t>& weighs, std::vector<std::vector<std::vector<int64_t>>>& edges, int64_t n, int64_t x, int64_t y)
    {
        int64_t index = std::find(weighs.cbegin(), weighs.cend(), n) - weighs.cbegin();

        for (int64_t j = 0; j < edges[index].size(); j++)
        {
            std::array<int64_t, 2> arr = { 0, 0 };

            for (int64_t k = 0; k < edges[index][j].size(); k++)
            {
                int64_t n = edges[index][j][k];

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
    bool Kruskal::AvailableInResult(std::vector<std::vector<int64_t>>& result, std::vector<int64_t>& vec)
    {
        for (int64_t i = 0; i < result.size(); i++)
        {
            if (vec.size() <= result[i].size())
            {
                std::array<int64_t, 2> arr = { 0, 0 };

                for (int64_t j = 0; j < result[i].size(); j++)
                {
                    int64_t n = result[i][j];

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

    void Kruskal::SetResult(std::vector<std::vector<int64_t>>& result, std::vector<int64_t>& vec, int64_t& last)
    {
        int64_t index_1 = GetIndexFromResult(result, vec[0]); // index of 'g'
        int64_t index_2 = GetIndexFromResult(result, vec[1]); // index of 'h'

        if (index_1 < 0 || index_2 < 0)
        {
            return;
        }

        if (result[index_1].size() >= result[index_2].size())
        {
            for (int64_t k = 0; k < result[index_2].size(); k++)
            {
                result[index_1].push_back(result[index_2][k]);
                result[index_2][k] = -1; // erasing
            }

            last = index_1;
            return;
        }

        if (result[index_2].size() >= result[index_1].size())
        {
            for (int64_t k = 0; k < result[index_1].size(); k++)
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
        std::cout << output;
    }
}