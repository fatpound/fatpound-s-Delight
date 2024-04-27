#pragma once

#include "Graph.hpp"

#include <memory>

namespace fatpound::graph
{
    class DFS final
    {
    public:
        DFS(const std::string& input_filename);

        DFS() = delete;
        DFS(const DFS& src) = delete;
        DFS& operator = (const DFS& src) = delete;
        DFS(DFS&& src) noexcept;
        DFS& operator = (DFS&& src) noexcept;
        ~DFS() = default;


    public:
        void PrintResults() const;


    protected:


    private:
        void Visit_(std::vector<fatpound::util::Color>& colors, const std::size_t& index);


    private:
        std::unique_ptr<Graph> graph_ = nullptr;

        std::string output_;
    };
}