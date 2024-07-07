#pragma once

#include "Graph.hpp"

#include <memory>

namespace fatpound::dsa::graph
{
    class Kruskal final
    {
    public:
        Kruskal(const std::string& input_filename);

        Kruskal() = delete;
        Kruskal(const Kruskal& src) = delete;
        Kruskal& operator = (const Kruskal& src) = delete;
        Kruskal(Kruskal&& src) noexcept;
        Kruskal& operator = (Kruskal&& src) noexcept;
        ~Kruskal() = default;


    public:
        void PrintResults() const;


    protected:


    private:
        std::int64_t GetIndexFromResult_(std::vector<std::vector<std::int64_t>>& result, const std::int64_t& value);

        bool IsNotInEdges_(std::vector<std::int64_t>& weighs, std::vector<std::vector<std::vector<std::int64_t>>>& edges, std::int64_t n, std::int64_t x, std::int64_t y);
        bool AvailableInResult_(std::vector<std::vector<std::int64_t>>& result, std::vector<std::int64_t>& vec);

        void SetResult_(std::vector<std::vector<std::int64_t>>& result, std::vector<std::int64_t>& vec, std::int64_t& last);


    private:
        std::unique_ptr<Graph> graph_ = nullptr;

        std::string output_;
    };
}