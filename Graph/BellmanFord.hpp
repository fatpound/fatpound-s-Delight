#pragma once

#include "Graph.hpp"

#include <memory>
#include <array>

namespace fatpound::graph
{
    class BellmanFord
    {
    public:
        BellmanFord() = delete;
        ~BellmanFord() = default;
        BellmanFord(const BellmanFord& src) = delete;
        BellmanFord(BellmanFord&& src) noexcept;
        BellmanFord& operator = (const BellmanFord& src) = delete;
        BellmanFord& operator = (BellmanFord&& src) noexcept;

        BellmanFord(const std::string& input_filename, size_t source_index);

    public:
        void PrintResults() const;


    protected:


    private:
        inline void relax(std::vector<int64_t>& d, std::vector<int64_t>& p, const size_t u, const size_t v);

        inline int64_t w(const size_t u, const size_t v);


    private:
        std::unique_ptr<Graph> G = nullptr;

        std::string output;
    };
}