#pragma once

#include "Graph.hpp"

#include <memory>

namespace fatpound::graph
{
    class Kruskal
    {
    public:
        Kruskal() = delete;
        ~Kruskal() = default;
        Kruskal(const Kruskal& src) = delete;
        Kruskal(Kruskal&& src) noexcept;
        Kruskal& operator = (const Kruskal& src) = delete;
        Kruskal& operator = (Kruskal&& src) noexcept;

        Kruskal(const std::string& input_filename);


    public:
        void PrintResults() const;


    protected:


    private:
        int64_t GetIndexFromResult(std::vector<std::vector<int64_t>>& result, const int64_t& value);

        bool IsNotInEdges(std::vector<int64_t>& weighs, std::vector<std::vector<std::vector<int64_t>>>& edges, int64_t n, int64_t x, int64_t y);
        bool AvailableInResult(std::vector<std::vector<int64_t>>& result, std::vector<int64_t>& vec);

        void SetResult(std::vector<std::vector<int64_t>>& result, std::vector<int64_t>& vec, int64_t& last);


    private:
        std::unique_ptr<Graph> graph_ = nullptr;

        std::string output_;
    };
}