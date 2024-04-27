#pragma once

#include "Graph.hpp"

#include <memory>

namespace fatpound::graph
{
    class Prim final
    {
    
    public:
        Prim(const std::string& input_filename);

        Prim() = delete;
        Prim(const Prim& src) = delete;
        Prim& operator = (const Prim& src) = delete;
        Prim(Prim&& src) noexcept;
        Prim& operator = (Prim&& src) noexcept;
        ~Prim() = default;


    public:
        void PrintResults() const;


    protected:


    private:
        std::unique_ptr<Graph> graph_ = nullptr;

        std::string output_;
    };
}