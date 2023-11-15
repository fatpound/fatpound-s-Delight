#include "Prim.hpp"

#include <deque>

namespace fatpound::graph
{
    Prim::Prim(Prim&& src) noexcept
    {
        G = std::move(src.G);
        output = std::move(src.output);
    }
    Prim& Prim::operator = (Prim&& src) noexcept
    {
        G = std::move(src.G);
        output = std::move(src.output);

        return *this;
    }

    Prim::Prim(const std::string& input_filename)
        :
        G{ std::make_unique<Graph>(input_filename) }
    {
        std::vector<int64_t> key;
        std::vector<int64_t> pi;

        std::deque<int64_t> deque;

        size_t item_count = G->GetNodeCount();

        for (size_t i = 0; i < item_count; i++)
        {
            key.push_back(INT64_MAX);
            pi.push_back(-1ll);

            deque.push_back(int64_t(i));
        }

        key[0] = 0;

        while (item_count > 0)
        {
            size_t min_index = 0;

            bool flag = true; // does min_index need to be initialized ?

            for (size_t i = 0; i < deque.size(); i++)
            {
                if (deque[i] == int64_t(i))
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

            const size_t u = size_t(deque[min_index]);

            deque[min_index] = -1LL;
            item_count--;

            for (size_t i = 0; i < G->GetNodeAt(u)->next.size(); i++)
            {
                const size_t v = G->GetNodeAt(u)->next[i];
                const int64_t next_val = G->GetNodeAt(v)->n;

                if (deque[v] == int64_t(v) && key[v] > next_val)
                {
                    key[v] = next_val;
                    pi[v] = int64_t(u);
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
                ss << (char)('a' + pi[i]) << ' ';
            }
            else
            {
                ss << "N ";
            }
        }

        ss << "\n\n";

        output += std::move(ss.str());
    }

    void Prim::PrintResults() const
    {
        std::cout << output;
    }
}