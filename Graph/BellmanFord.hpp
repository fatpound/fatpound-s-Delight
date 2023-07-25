#pragma once

#include "graph.hpp"

namespace fatpound::graph
{
    class BellmanFord
    {
    private:
        std::array<std::vector<std::array<std::size_t, 2>>, 3> edges;
        std::vector<std::int64_t> d;
        std::vector<std::int64_t> p;

        graph* G = nullptr;

        std::int64_t w(const std::size_t u, const std::size_t v);

        void relax(const std::size_t u, const std::size_t v);

        bool run_private();

    protected:


    public:
        BellmanFord(graph* graf, std::size_t source_index);
        ~BellmanFord();

        void run();
    };

    std::int64_t BellmanFord::w(const std::size_t u, const std::size_t v)
    {
        return this->G->adj.at(u).at(v);
    }

    BellmanFord::BellmanFord(graph* graf, std::size_t source_index)
    {
        if (graf == nullptr)
            return;

        this->G = graf;

        for (std::size_t i = 0; i < graf->nodes.size(); i++)
        {
            this->d.push_back(99999); // INT64_MAX
            this->p.push_back(-1);
        }

        this->d.at(source_index) = 0;

        std::vector<std::array<std::size_t, 2>> new_vec1;
        std::vector<std::array<std::size_t, 2>> new_vec2;
        std::vector<std::array<std::size_t, 2>> new_vec3;

        for (std::size_t i = 0; i < this->G->nodes.size(); i++)
        {
            for (std::size_t j = 0; j < this->G->nodes.at(i)->next_list.size(); j++)
            {
                const std::size_t dest_index = this->G->nodes.at(i)->next_list.at(j)->n;

                std::array<std::size_t, 2> new_edge{i, dest_index};

                if (i == source_index)
                    new_vec2.push_back(new_edge);
                else
                {
                    if (i < dest_index)
                        new_vec1.push_back(new_edge);
                    else
                        new_vec3.push_back(new_edge);
                }
            }
        }

        this->edges.at(0) = new_vec1;
        this->edges.at(1) = new_vec2;
        this->edges.at(2) = new_vec3;
    }
    BellmanFord::~BellmanFord()
    {
        this->G->~graph();
    }

    bool BellmanFord::run_private()
    {
        for (std::size_t i = 0; i < this->G->nodes.size() - 1; i++)
        {
            for (std::size_t j = 0; j < this->edges.size(); j++)
            {
                for (std::size_t k = 0; k < this->edges.at(j).size(); k++)
                {
                    const std::size_t u = this->edges.at(j).at(k).at(0);
                    const std::size_t v = this->edges.at(j).at(k).at(1);

                    this->relax(u, v);
                }
            }
        }

        for (std::size_t i = 0; i < this->edges.size(); i++)
        {
            for (std::size_t j = 0; j < this->edges.at(i).size(); j++)
            {
                const std::size_t u = this->edges.at(i).at(j).at(0);
                const std::size_t v = this->edges.at(i).at(j).at(1);

                std::int64_t w_val = this->w(u, v);

                if (this->d.at(v) > this->d.at(u) + w_val)
                    return false;
            }
        }

        // RESULTS
        for (std::size_t x = 0; x < this->d.size(); x++)
            std::cout << this->d.at(x) << ' ';

        std::cout << '\n';

        for (std::size_t x = 0; x < this->p.size(); x++)
        {
            if (this->p.at(x) > -1)
            {
                std::cout << (char)('A' + this->p.at(x));
            }
            else
                std::cout << 'N';
        }

        std::cout << "\n\n";

        return true;
    }

    void BellmanFord::relax(const std::size_t u, const std::size_t v)
    {
        if (this->d.at(v) > this->d.at(u) + this->w(u, v))
        {
            this->d.at(v) = this->d.at(u) + this->w(u, v);
            this->p.at(v) = (std::int64_t)u;
        }
    }
    void BellmanFord::run()
    {
        if ( this->G == nullptr || ! this->run_private())
            std::cout << "Hata";
    }
}