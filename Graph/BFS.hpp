#pragma once

#include "Graph.hpp"

#include <memory>

namespace fatpound::graph
{
    class BFS
    {
    public:
        BFS() = delete;
        ~BFS() = default;
        BFS(const BFS& src) = delete;
        BFS(BFS&& src) noexcept;
        BFS& operator = (const BFS& src) = delete;
        BFS& operator = (BFS&& src) noexcept;

        BFS(const std::string& inputFilename);


    public:
        void PrintResults() const;


    protected:


    private:
        std::unique_ptr<Graph> graph_ = nullptr;

        std::string output_;
    };
}