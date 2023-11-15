#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../Color/Color.hpp"

namespace fatpound::graph
{
    class Graph
    {
    private:
        struct node
        {
            std::vector<size_t> next;

            size_t n = 0;

            node() = default;
            ~node() = default;
            node(const node& src) noexcept;
            node(node&& src) = default;
            Graph::node& operator = (const node& src) noexcept;
            Graph::node& operator = (node&& src) = default;

            node(const size_t index);

            std::vector<size_t>& GetNextIndexesList();
            size_t GetNextIndexesListSize();
        };


    public:
        Graph() = default;
        ~Graph() noexcept;
        Graph(const Graph& src) noexcept;
        Graph(Graph&& src) noexcept;
        Graph& operator = (const Graph& src) noexcept;
        Graph& operator = (Graph&& src) noexcept;

        Graph(const std::string input_filename);


    public:
        Graph::node* GetNodeAt(const int64_t i) const;
        
        int64_t GetAdjAt(const int64_t u, const int64_t v) const;

        size_t GetNodeCount() const;
        size_t GetEdgeCount() const;

        void PrintNodes() const;


    protected:


    private:
        void Delete() noexcept;


    private:
        std::vector<std::vector<int64_t>> adj;
        std::vector<node*> nodes;

        size_t nodeCount = 0;
        size_t edgeCount = 0;
    };
}