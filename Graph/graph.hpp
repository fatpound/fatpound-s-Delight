#pragma once

#include "fatpound.hpp"

namespace fatpound
{
    namespace graph
    {
        class graph
        {
        private:
            class node
            {
            private:


            protected:


            public:
                std::vector<graph::node*> next_list;
                int n = -1;

                node();
                ~node();

                void list_all_adj();
            };


        protected:


        public:
            std::vector<std::vector<int>> adj;
            std::vector<graph::node*> nodes;

            int node_count = 0;
            int edge_count = 0;

            graph();
            ~graph();
            graph(std::string);
            graph(std::vector<std::vector<int>> vec);

            void list_nodes();
        };

        graph::node::node()
        {

        }
        graph::node::~node()
        {

        }

        void graph::node::list_all_adj()
        {
            for (int i = 0; i < this->next_list.size(); i++)
            {
                std::cout << this->next_list.at(i) << "\t" << this->next_list.at(i)->n << '\n';
            }
        }

        graph::graph()
        {

        }
        graph::~graph()
        {

        }
        graph::graph(std::string str)
        {
            std::fstream my_file;
            my_file.open(str, std::ios::in | std::ios::binary);

            while (my_file.eof() == false)
            {
                std::string str;
                getline(my_file, str);

                std::stringstream ss;
                ss << str;

                std::vector<int> vec;

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

            for (int i = 0; i < this->adj.size(); i++)
            {
                this->nodes.push_back(new node());
                this->nodes.at(i)->n = i;
            }

            for (int i = 0; i < this->adj.size(); i++)
            {
                for (int j = 0; j < this->adj.size(); j++)
                {
                    if (this->adj.at(i).at(j) != 0)
                    {
                        this->nodes.at(i)->next_list.push_back(this->nodes.at(j));
                        this->edge_count++;
                    }
                }
            }
        }
        graph::graph(std::vector<std::vector<int>> vec)
        {
            this->adj = std::vector<std::vector<int>>(vec);
            this->node_count = this->adj.size();

            for (int i = 0; i < this->adj.size(); i++)
            {
                this->nodes.push_back(new node());
                this->nodes.at(i)->n = i;
            }

            for (int i = 0; i < this->adj.size(); i++)
            {
                for (int j = 0; j < this->adj.size(); j++)
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
            for (int i = 0; i < this->nodes.size(); i++)
            {
                std::cout << this->nodes.at(i) << "\t" << this->nodes.at(i)->n << "\tsource\n";
                this->nodes.at(i)->list_all_adj();
                std::cout << "----------------" << '\n';
            }

            std::cout << '\n';
        }
    }
}