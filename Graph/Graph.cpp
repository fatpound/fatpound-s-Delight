#include "Graph.hpp"

namespace fatpound::graph
{
    Graph::node::node(const node& src) noexcept
        :
        n{ src.n },
        next{ src.next }
    {}
    Graph::node& Graph::node::operator = (const node & src) noexcept
    {
        n = src.n;
        next = src.next;

        return *this;
    }

    Graph::node::node(const size_t index)
        :
        n(index)
    {}

    std::vector<size_t>& Graph::node::GetNextIndexesList()
    {
        return next;
    }
    size_t Graph::node::GetNextIndexesListSize()
    {
        return next.size();
    }


    Graph::~Graph() noexcept
    {
        Delete();
    }
    Graph::Graph(const Graph& src) noexcept
    {
        if (src.nodeCount != 0)
        {
            nodeCount = src.nodeCount;
            edgeCount = src.edgeCount;

            adj = src.adj;

            for (size_t i = 0; i < nodeCount; i++)
            {
                nodes.push_back(new Graph::node(*src.nodes[i]));
            }
        }
    }
    Graph::Graph(Graph&& src) noexcept
    {
        if (src.nodeCount != 0)
        {
            nodes = std::move(src.nodes);
            adj = std::move(src.adj);

            nodeCount = src.nodeCount;
            edgeCount = src.edgeCount;

            src.nodeCount = 0;
            src.edgeCount = 0;
        }
    }
    Graph& Graph::operator = (const Graph& src) noexcept
    {
        if (this != std::addressof(src) && src.nodeCount != 0)
        {
            if (nodeCount != 0)
            {
                Delete();
            }

            nodeCount = src.nodeCount;
            edgeCount = src.edgeCount;

            adj = src.adj;

            for (size_t i = 0; i < nodeCount; i++)
            {
                nodes.push_back(new Graph::node(*src.nodes[i]));
            }
        }

        return *this;
    }
    Graph& Graph::operator = (Graph&& src) noexcept
    {
        if (this != std::addressof(src) && src.nodeCount != 0)
        {
            if (nodeCount != 0)
            {
                Delete();
            }

            nodes = std::move(src.nodes);
            adj = std::move(src.adj);

            nodeCount = src.nodeCount;
            edgeCount = src.edgeCount;

            src.nodeCount = 0;
            src.edgeCount = 0;
        }

        return *this;
    }

    Graph::Graph(const std::string input_filename)
    {
        {
            std::ifstream my_file(input_filename, std::ios_base::binary);

            if (!my_file.is_open())
            {
                return;
            }

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

        for (size_t i = 0; i < nodeCount; i++)
        {
            nodes.push_back(new node(i));
        }

        for (size_t i = 0; i < nodeCount; i++)
        {
            for (size_t j = 0; j < nodeCount; j++)
            {
                if (adj[i][j] != 0)
                {
                    nodes[i]->next.push_back(j);
                    edgeCount++;
                }
            }
        }
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
        for (size_t i = 0; i < nodeCount; i++)
        {
            std::cout << nodes[i] << "\t" << nodes[i]->n << "\tsource\n";

            for (size_t j = 0; j < nodes[i]->next.size(); j++)
            {
                std::cout << nodes[i]->next[j];
            }

            std::cout << "----------------\n";
        }

        std::cout << "\n";
    }

    void Graph::Delete() noexcept
    {
        for (size_t i = 0ull; i < nodeCount; i++)
        {
            delete nodes[i];
        }

        nodes.clear();
        adj.clear();

        nodeCount = 0ull;
        edgeCount = 0ull;
    }
}