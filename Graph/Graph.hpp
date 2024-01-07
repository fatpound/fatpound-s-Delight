#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>

#include "../Color/Color.hpp"

namespace fatpound::graph
{
    class Graph
    {
    public:
        Graph() = delete;

        Graph(const std::string input_filename);


    public:
        const std::vector<int64_t>& const GetNextList(size_t index) const;

        const int64_t GetAdjAt(const int64_t u, const int64_t v) const;

        const size_t GetNodeCount() const;
        const size_t GetEdgeCount() const;


    protected:


    private:
        std::vector<std::vector<int64_t>> adj_;
        std::vector<std::vector<int64_t>> nexts_;

        size_t node_count_ = 0;
        size_t edge_count_ = 0;
    };
}