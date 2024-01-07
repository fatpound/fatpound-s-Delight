#pragma once

#include "Graph.hpp"

#include <memory>

namespace fatpound::graph
{
    class DFS
    {
    public:
        DFS() = delete;
        ~DFS() = default;
        DFS(const DFS& src) = delete;
        DFS(DFS&& src) noexcept;
        DFS& operator = (const DFS& src) = delete;
        DFS& operator = (DFS&& src) noexcept;

        DFS(const std::string& input_filename);


    public:
        void PrintResults() const;


    protected:


    private:
        void Visit(std::vector<fatpound::color::Color>& colors, const size_t& index);


    private:
        std::unique_ptr<Graph> graph_ = nullptr;

        std::string output_;
    };
}