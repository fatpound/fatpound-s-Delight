#pragma once

#include "Color.hpp"

namespace fatpound::graph
{
    class Graph
    {
    private:
        class node
        {
        private:


        protected:


        public:
            std::vector<size_t> next;

            size_t n = 0;

            node() = delete;
            node(const size_t index);
        };

        std::vector<std::vector<int64_t>> adj;
        std::vector<node*> nodes;

        std::string str;

        size_t nodeCount = 0;
        size_t edgeCount = 0;


    protected:


    public:
        Graph() = default;
        ~Graph() noexcept;
        Graph(const Graph& src) = delete;
        Graph(Graph&& src) = delete;
        Graph& operator = (const Graph& src) = delete;
        Graph& operator = (Graph&& src) = delete;

        Graph(const std::string input_filename);

        Graph::node* GetNodeAt(const int64_t i) const;

        int64_t GetAdjAt(const int64_t u, const int64_t v) const;

        size_t GetNodeCount() const;
        size_t GetEdgeCount() const;

        void PrintNodes() const;
    };


    Graph::node::node(const size_t index)
        :
        n(index)
    {
    }

    Graph::~Graph() noexcept
    {
        for (size_t i = 0; i < nodes.size(); i++)
        {
            delete nodes[i];
        }
    }
    Graph::Graph(const std::string input_filename)
    {
        {
            std::ifstream my_file(input_filename, std::ios_base::binary);

            if (!my_file.is_open())
                return;
            
            while (my_file.eof() == false)
            {
                std::string line;
                getline(my_file, line);

                std::stringstream ss;
                ss << line;

                std::vector<int64_t> vec;

                while (ss.eof() == false)
                {
                    int64_t x;
                    ss >> x >> std::ws;

                    vec.push_back(x);
                }

                adj.push_back(std::move(vec));
            }

            my_file.close();
        }

        nodeCount = adj.size();

        for (size_t i = 0; i < adj.size(); i++)
        {
            nodes.push_back(new node(i));
        }

        for (size_t i = 0; i < adj.size(); i++)
        {
            for (size_t j = 0; j < adj.size(); j++)
            {
                if (adj[i][j] != 0)
                {
                    nodes[i]->next.push_back(j);
                    edgeCount++;
                }
            }
        }

        std::stringstream ss;

        for (size_t i = 0; i < nodes.size(); i++)
        {
            ss << nodes[i] << "\t" << nodes[i]->n << "\tsource\n";

            for (size_t j = 0; j < nodes[i]->next.size(); j++)
            {
                ss << nodes[i]->next[j];
            }

            ss << "----------------\n";
        }

        ss << "\n";

        str = std::move(ss.str());
    }

    Graph::node* Graph::GetNodeAt(const int64_t i) const
    {
        return nodes[i];
    }
    
    int64_t Graph::GetAdjAt(const int64_t u, const int64_t v) const
    {
        return adj[u][v];
    }

    size_t Graph::GetNodeCount() const
    {
        return nodeCount;
    }
    size_t Graph::GetEdgeCount() const
    {
        return edgeCount;
    }

    void Graph::PrintNodes() const
    {
        std::cout << str;
    }
}