#pragma once

#include "Graph.hpp"

#include <memory>

namespace fatpound::graph
{
    class BellmanFord
    {
    public:
        BellmanFord(const std::string& input_filename, std::size_t source_index = 0u);

        BellmanFord() = delete;
        BellmanFord(const BellmanFord& src) = delete;
        BellmanFord& operator = (const BellmanFord& src) = delete;
        BellmanFord(BellmanFord&& src) noexcept;
        BellmanFord& operator = (BellmanFord&& src) noexcept;
        ~BellmanFord() = default;



    public:
        void PrintResults() const;


    protected:


    private:
        std::int64_t w_(const std::size_t& u, const std::size_t& v);

        void relax_(std::vector<std::int64_t>& d, std::vector<std::int64_t>& p, const std::size_t& u, const std::size_t& v);


    private:
        std::unique_ptr<Graph> graph_ = nullptr;

        std::string output_;
    };
}