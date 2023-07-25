#pragma once

#include "fatpound.hpp"

namespace fatpound
{
    namespace graph
    {
        static constexpr std::int64_t color_white = 0;
        static constexpr std::int64_t color_gray  = 1;
        static constexpr std::int64_t color_black = 2;

        class graph
        {
        private:
            class node
            {
            private:


            protected:


            public:
                std::vector<graph::node*> next_list;
                std::size_t n = 0;

                node(std::size_t idx);
                ~node();

                void list_all_adj();
            };

            std::size_t is_deleted = 0; // this isn't bool just to avoid C4820


        protected:


        public:
            std::vector<std::vector<std::int64_t>> adj;
            std::vector<graph::node*> nodes;

            std::size_t node_count = 0;
            std::size_t edge_count = 0;

            graph();
            ~graph();
            graph(std::string);
            graph(std::vector<std::vector<std::int64_t>>& vec);

            void list_nodes();
        };

        graph::node::node(std::size_t idx)
        {
            this->n = idx;
        }
        graph::node::~node()
        {

        }

        void graph::node::list_all_adj()
        {
            for (std::size_t i = 0; i < this->next_list.size(); i++)
            {
                std::cout << this->next_list.at(i) << "\t" << this->next_list.at(i)->n << '\n';
            }
        }

        graph::graph()
        {

        }
        graph::~graph()
        {
            if (this->is_deleted == 1)
                return;

            for (std::size_t i = 0; i < this->nodes.size(); i++)
                delete this->nodes.at(i);

            this->is_deleted = 1;
        }
        graph::graph(std::string str)
        {
            std::fstream my_file;
            my_file.open(str, std::ios::in | std::ios::binary);

            while (my_file.eof() == false)
            {
                std::string str2;
                getline(my_file, str2);

                std::stringstream ss;
                ss << str2;

                std::vector<std::int64_t> vec;

                while (ss.eof() == false)
                {
                    int x;
                    ss >> x >> std::ws;

                    vec.push_back(x);
                }

                this->adj.push_back(vec);
            }

            my_file.close();

            this->node_count = this->adj.size();

            for (std::size_t i = 0; i < this->adj.size(); i++)
            {
                this->nodes.push_back(new graph::node(i));
            }

            for (std::size_t i = 0; i < this->adj.size(); i++)
            {
                for (std::size_t j = 0; j < this->adj.size(); j++)
                {
                    if (this->adj.at(i).at(j) != 0)
                    {
                        this->nodes.at(i)->next_list.push_back(this->nodes.at(j));
                        this->edge_count++;
                    }
                }
            }
        }
        graph::graph(std::vector<std::vector<std::int64_t>>& vec)
        {
            this->adj = vec;
            this->node_count = this->adj.size();

            for (std::size_t i = 0; i < this->adj.size(); i++)
            {
                this->nodes.push_back(new graph::node(i));
            }

            for (std::size_t i = 0; i < this->adj.size(); i++)
            {
                for (std::size_t j = 0; j < this->adj.size(); j++)
                {
                    if (this->adj.at(i).at(j) != 0)
                    {
                        this->nodes.at(i)->next_list.push_back(this->nodes.at(j));
                        this->edge_count++;
                    }
                }
            }
        }

        void graph::list_nodes()
        {
            for (std::size_t i = 0; i < this->nodes.size(); i++)
            {
                std::cout << this->nodes.at(i) << "\t" << this->nodes.at(i)->n << "\tsource\n";
                this->nodes.at(i)->list_all_adj();
                std::cout << "----------------" << '\n';
            }

            std::cout << '\n';
        }
    }
}