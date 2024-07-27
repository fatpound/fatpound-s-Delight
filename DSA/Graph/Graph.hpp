#pragma once

#include "../../Util/Color.hpp"

#include <cstdint>

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>
#include <limits>

namespace fatpound::dsa::graph
{
    class Graph final
    {
    public:
        Graph(const std::string& input_filename);

        Graph() = delete;
        Graph(const Graph& src) = delete;
        Graph& operator = (const Graph& src) = delete;
        Graph(Graph&& src) = delete;
        Graph& operator = (Graph&& src) = delete;
        ~Graph() = default;


    public:
        const std::vector<std::int64_t>& GetNextList(std::size_t index) const;

        std::int64_t GetAdjAt(const std::int64_t u, const std::int64_t v) const;

        std::size_t GetNodeCount() const;
        std::size_t GetEdgeCount() const;


    protected:


    private:
        std::vector<std::vector<std::int64_t>> adj_;
        std::vector<std::vector<std::int64_t>> nexts_;

        std::size_t node_count_ = 0u;
        std::size_t edge_count_ = 0u;
    };
}