#pragma once

#include "Graph.hpp"

#include <memory>

namespace fatpound::graph
{
    class Dijkstra
    {
    public:
        Dijkstra() = delete;
        ~Dijkstra() = default;
        Dijkstra(const Dijkstra& src) = delete;
        Dijkstra(Dijkstra&& src) noexcept;
        Dijkstra& operator = (const Dijkstra& src) = delete;
        Dijkstra& operator = (Dijkstra&& src) noexcept;

        Dijkstra(const std::string& input_filename, size_t source_index = 0u);


    public:
        void PrintResults() const;


    protected:


    private:
        int64_t w(const size_t& u, const size_t& v) const;

        void relax(std::vector<int64_t>& d, std::vector<int64_t>& p, const size_t& u, const size_t& v);


    private:
        std::unique_ptr<Graph> graph_ = nullptr;

        std::string output_;
    };
}