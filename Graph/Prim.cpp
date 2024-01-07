#include "Prim.hpp"

#include <deque>

namespace fatpound::graph
{
    Prim::Prim(Prim&& src) noexcept
        :
        graph_(std::move(src.graph_)),
        output_(std::move(src.output_))
    {
        
    }
    Prim& Prim::operator = (Prim&& src) noexcept
    {
        graph_  = std::move(src.graph_);
        output_ = std::move(src.output_);

        return *this;
    }

    Prim::Prim(const std::string& input_filename)
        :
        graph_(std::make_unique<Graph>(input_filename))
    {
        std::vector<int64_t> key;
        std::vector<int64_t> pi;

        std::deque<int64_t> deque;

        size_t item_count = graph_->GetNodeCount();

        for (size_t i = 0; i < item_count; ++i)
        {
            key.push_back(std::numeric_limits<int64_t>::max());
            pi.push_back(-1);

            deque.push_back(static_cast<int64_t>(i));
        }

        key[0] = 0;

        while (item_count > 0)
        {
            size_t min_index = 0;

            bool flag = true; // does min_index need to be initialized ?

            for (size_t i = 0; i < deque.size(); ++i)
            {
                if (deque[i] == static_cast<int64_t>(i))
                {
                    if (flag)
                    {
                        min_index = i;
                        flag = false;
                    }

                    if (key[min_index] > key[i])
                    {
                        min_index = i;
                    }
                }
            }

            const size_t u = static_cast<size_t>(deque[min_index]);

            deque[min_index] = -1;

            --item_count;

            for (size_t i = 0; i < graph_->GetNextList(u).size(); ++i)
            {
                const size_t v = graph_->GetNextList(u)[i];
                const int64_t next_val = graph_->GetAdjAt(u, v);

                if (deque[v] == static_cast<int64_t>(v) && key[v] > next_val)
                {
                    key[v] = next_val;
                    pi[v] = static_cast<int64_t>(u);
                }
            }
        }

        std::stringstream ss;

        for (size_t i = 0; i < key.size(); i++)
        {
            ss << key[i] << ' ';
        }

        ss << '\n';

        for (size_t i = 0; i < pi.size(); i++)
        {
            if (pi[i] != -1)
            {
                ss << static_cast<char>('a' + pi[i]) << ' ';
            }
            else
            {
                ss << "N ";
            }
        }

        ss << "\n\n";

        output_ += std::move(ss.str());
    }


    void Prim::PrintResults() const
    {
        std::cout << output_;
    }
}