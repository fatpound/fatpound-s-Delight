#include "Graph.hpp"

namespace fatpound::graph
{
    Graph::Graph(const std::string& input_filename)
    {
        std::ifstream my_file(input_filename, std::ios_base::binary);

        if ( ! my_file.is_open() )
        {
            throw std::runtime_error("Input file cannot be opened!");
        }

        while ( ! my_file.eof() )
        {
            std::string line;
            std::getline(my_file, line);

            std::stringstream ss;
            ss << line;

            std::vector<int64_t> vec;

            while ( ! ss.eof() )
            {
                int64_t x;
                ss >> x >> std::ws;

                vec.push_back(x);
            }

            adj_.push_back(std::move(vec));
            nexts_.emplace_back();
        }

        my_file.close();

        node_count_ = adj_.size();

        for (size_t i = 0; i < node_count_; i++)
        {
            for (size_t j = 0; j < node_count_; j++)
            {
                if (adj_[i][j] != 0)
                {
                    nexts_[i].push_back(j);

                    ++edge_count_;
                }
            }
        }
    }


    const std::vector<int64_t>& const Graph::GetNextList(size_t index) const
    {
        return nexts_[index];
    }

    const int64_t Graph::GetAdjAt(const int64_t u, const int64_t v) const
    {
        return adj_[u][v];
    }

    const size_t Graph::GetNodeCount() const
    {
        return node_count_;
    }
    const size_t Graph::GetEdgeCount() const
    {
        return edge_count_;
    }
}