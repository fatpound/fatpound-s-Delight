#pragma once

#include "Graph.hpp"

#include <memory>

namespace fatpound::graph
{
    class BFS final
    {
    public:
        BFS(const std::string& input_filename);

        BFS() = delete;
        BFS(const BFS& src) = delete;
        BFS& operator = (const BFS& src) = delete;
        BFS(BFS&& src) noexcept;
        BFS& operator = (BFS&& src) noexcept;
        ~BFS() = default;


    public:
        void PrintResults() const;


    protected:


    private:
        std::unique_ptr<Graph> graph_ = nullptr;

        std::string output_;
    };
}