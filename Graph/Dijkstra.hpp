#pragma once

#include "Graph.hpp"

#include <memory>

namespace fatpound::graph
{
    class Dijkstra final
    {
    public:
        Dijkstra(const std::string& input_filename, std::size_t source_index = 0u);

        Dijkstra() = delete;
        Dijkstra(const Dijkstra& src) = delete;
        Dijkstra& operator = (const Dijkstra& src) = delete;
        Dijkstra(Dijkstra&& src) noexcept;
        Dijkstra& operator = (Dijkstra&& src) noexcept;
        ~Dijkstra() = default;


    public:
        void PrintResults() const;


    protected:


    private:
        std::int64_t w_(const std::size_t& u, const std::size_t& v) const;

        void relax_(std::vector<std::int64_t>& d, std::vector<std::int64_t>& p, const std::size_t& u, const std::size_t& v);


    private:
        std::unique_ptr<Graph> graph_ = nullptr;

        std::string output_;
    };
}