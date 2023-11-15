#pragma once

#include "Graph.hpp"

#include <memory>

namespace fatpound::graph
{
    class Prim
    {
    
    public:
        Prim() = delete;
        ~Prim() = default;
        Prim(const Prim& src) = delete;
        Prim(Prim&& src) noexcept;
        Prim& operator = (const Prim& src) = delete;
        Prim& operator = (Prim&& src) noexcept;

        Prim(const std::string& input_filename);


    public:
        void PrintResults() const;


    protected:


    private:
        std::unique_ptr<Graph> G = nullptr;

        std::string output;
    };
}