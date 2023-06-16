#pragma once

#include "graph.hpp"

namespace fatpound
{
    namespace graph
    {
        class Prim
        {
        private:
            std::deque<int> deque;

            std::vector<int> key;
            std::vector<int> pi;

            graph* G = nullptr;

            int item_count = 0;


        protected:


        public:
            Prim(graph* graf);

            void run();
        };

        Prim::Prim(graph* graf)
        {
            this->G = graf;

            for (int i = 0; i < this->G->nodes.size(); i++)
            {
                this->key.push_back(999); // INT32_MAX
                this->pi.push_back(-1);

                this->deque.push_back(i);
                this->item_count++;
            }
        }

        void Prim::run()
        {
            this->key.at(0) = 0;

            while (this->item_count > 0)
            {
                int min_index = -1;

                for (int i = 0; i < this->deque.size(); i++)
                {
                    if (this->deque.at(i) == i)
                    {
                        if (min_index == -1)
                            min_index = i;

                        if (this->key.at(min_index) > this->key.at(i))
                        {
                            min_index = i;
                        }
                    }
                }

                int u = this->deque.at(min_index);
                this->deque.at(min_index) = -1;
                this->item_count--;

                for (int i = 0; i < this->G->nodes.at(u)->next_list.size(); i++)
                {
                    int v = this->G->nodes.at(u)->next_list.at(i)->n;
                    if (this->deque.at(v) == v && (this->key.at(v) > this->G->adj.at(u).at(v)))
                    {
                        this->key.at(v) = this->G->adj.at(u).at(v);
                        this->pi.at(v) = u;
                    }
                }
            }

            for (int i = 0; i < this->key.size(); i++)
            {
                std::cout << this->key.at(i) << ' ';
            }

            std::cout << '\n';

            for (int i = 0; i < this->pi.size(); i++)
            {
                if (this->pi.at(i) != -1)
                {
                    std::cout << "abcdefghi"[this->pi.at(i)] << ' ';
                }
                else
                    std::cout << "N ";
            }

            std::cout << '\n';
        }
    }
}