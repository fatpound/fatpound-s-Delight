#pragma once

#include "graph.hpp"

namespace fatpound
{
    namespace graph
    {
        class Prim
        {
        private:
            std::deque<std::int64_t> deque;

            std::vector<std::int64_t> key;
            std::vector<std::int64_t> pi;

            graph* G = nullptr;

            std::size_t item_count = 0;


        protected:


        public:
            Prim(graph* graf);

            void run();
        };

        Prim::Prim(graph* graf)
        {
            this->G = graf;

            for (std::size_t i = 0; i < this->G->nodes.size(); i++)
            {
                this->key.push_back(999); // INT32_MAX
                this->pi.push_back(-1);

                this->deque.push_back((std::int64_t)i);
                this->item_count++;
            }
        }

        void Prim::run()
        {
            if (this->G == nullptr)
                return;

            this->key.at(0) = 0;

            while (this->item_count > 0)
            {
                std::size_t min_index = 0;

                bool flag = true; // does min_index need to be initialized ?
                
                for (std::size_t i = 0; i < this->deque.size(); i++)
                {
                    if (this->deque.at(i) == (std::int64_t)i)
                    {
                        if (flag)
                        {
                            min_index = i;
                            flag = false;
                        }

                        if (this->key.at(min_index) > this->key.at(i))
                            min_index = i;
                    }
                }

                const std::size_t u = (std::size_t)this->deque.at(min_index);

                this->deque.at(min_index) = -1;
                this->item_count--;

                for (std::size_t i = 0; i < this->G->nodes.at(u)->next_list.size(); i++)
                {
                    const std::size_t v = this->G->nodes.at(u)->next_list.at(i)->n;

                    if (this->deque.at(v) == (std::int64_t)v && (this->key.at(v) > this->G->adj.at(u).at(v)))
                    {
                        this->key.at(v) = this->G->adj.at(u).at(v);
                        this->pi.at(v)  = (std::int64_t)u;
                    }
                }
            }

            for (std::size_t i = 0; i < this->key.size(); i++)
                std::cout << this->key.at(i) << ' ';

            std::cout << '\n';

            for (std::size_t i = 0; i < this->pi.size(); i++)
            {
                if (this->pi.at(i) != -1)
                {
                    std::cout << (char)('a' + this->pi.at(i)) << ' ';
                }
                else
                    std::cout << "N ";
            }

            std::cout << '\n';
        }
    }
}