#pragma once

#include "fatpound.hpp"

namespace fatpound
{
    namespace compression
    {
        class Huffman
        {
        private:
            class node
            {
            private:


            protected:


            public:
                Huffman::node* left = nullptr;
                Huffman::node* right = nullptr;

                std::string binary_val = "";

                char k  = '\0';
                int num =   0;

                node();
                ~node();
                node(char new_k, int new_num);
                node(Huffman::node* sol, Huffman::node* sag);
            };

            std::vector<char>        results_chars;
            std::vector<std::string> results_binary;

            void set_binary_values_private(Huffman::node* node, std::string str);
            void list_preorder_private(Huffman::node* node);


        protected:


        public:
            Huffman::node* root = nullptr;

            int node_count = 0;
            int leaf_count = 0;

            int min_depth  = INT32_MAX;
            int max_depth  = INT32_MIN;

            void decompress(std::string bin);

            void list_preorder();
            void list_results();

            Huffman();
            ~Huffman();
            Huffman(std::string input);
        };

        Huffman::node::node()
        {

        }
        Huffman::node::~node()
        {

        }
        Huffman::node::node(char new_k, int new_num)
        {
            this->k   = new_k;
            this->num = new_num;
        }
        Huffman::node::node(Huffman::node* sol, Huffman::node* sag)
        {
            this->k     = '\0';
            this->num   = sol->num + sag->num;

            this->left  = sol;
            this->right = sag;
        }

        Huffman::Huffman()
        {

        }
        Huffman::~Huffman()
        {

        }
        Huffman::Huffman(std::string input)
        {
            std::vector<char> chars;
            std::vector<int> counts;

            for (auto x : input)
            {
                int index = -1;

                for (int i = 0; i < chars.size(); i++)
                    if (chars.at(i) == x)
                        index = i;

                if (index == -1)
                {
                    chars.push_back(x);
                    counts.push_back(1);
                }
                else
                    counts.at(index)++;
            }

            this->leaf_count = chars.size();

            for (int i = 0; i < chars.size(); i++)
            {
                std::cout << chars.at(i) << ' ' << counts.at(i) << '\n';
            }
            
            std::cout << '\n';

            std::vector<std::pair<int, char>> pairs;

            for (int i = 0; i < this->leaf_count; i++)
                pairs.push_back(std::pair<int, char>(counts.at(i), chars.at(i))); // counts first

            std::sort(pairs.begin(), pairs.end());

            for (int i = 0; i < pairs.size(); i++)
            {
                counts.at(i) = pairs.at(i).first;
                chars.at(i) = pairs.at(i).second;
            }

            for (int i = 0; i < pairs.size(); i++)
            {
                std::cout << chars.at(i) << ' ' << counts.at(i) << '\n';
            }

            std::cout << '\n';

            std::deque<Huffman::node*> deque;

            for (int i = 0; i < this->leaf_count; i++)
            {
                deque.push_back(new node(chars.at(i), counts.at(i)));
            }

            int n = deque.size();

            for (int i = 0; i < n - 1; i++)
            {
                Huffman::node* sol = deque.at(0);
                Huffman::node* sag = deque.at(1);

                Huffman::node* yeni_dugum = new Huffman::node(sol, sag);

                deque.pop_front();
                deque.pop_front();

                int index = 0;

                for (int j = 0; j < deque.size(); j++)
                {
                    if (yeni_dugum->num > deque.at(index)->num)
                    {
                        index = j + 1;
                    }
                    else break;
                }

                deque.insert(deque.begin() + index, yeni_dugum);
            }

            this->root = deque.at(0);
            this->node_count = n * 2 - 1;

            this->set_binary_values_private(this->root, "");
            std::cout << "min_depth: " << this->min_depth << '\n';
            std::cout << "max_depth: " << this->max_depth << '\n';
        }

        void Huffman::set_binary_values_private(Huffman::node* node, std::string str)
        {
            if (node == nullptr)
                return;

            if (node->left == nullptr && node->right == nullptr)
            {
                this->results_chars.push_back(node->k);
                this->results_binary.push_back(str);
                
                if (this->max_depth < (int)str.size())
                    this->max_depth = (int)str.size();
                
                if (this->min_depth > (int)str.size())
                    this->min_depth = (int)str.size();

                return;
            }

            this->set_binary_values_private(node->left, str + "0");
            this->set_binary_values_private(node->right, str + "1");
        }
        void Huffman::list_preorder_private(Huffman::node* node)
        {
            if (node == nullptr)
                return;

            if (node->left == nullptr && node->right == nullptr)
            {
                std::cout << node->k << '*' << node->num << ' ';
                return;
            }

            std::cout << node->num << ' ';
            this->list_preorder_private(node->left);
            this->list_preorder_private(node->right);
        }

        void Huffman::decompress(std::string bin)
        {
            std::string decompressed = "";

            for (int i = 0; i < bin.size(); i++)
            {
                std::string temp = "";

                int index = -1;

                for (int j = i; j < bin.size() && temp.size() <= this->max_depth; j++)
                {
                    temp += bin.at(j);

                    if (temp.size() < this->min_depth)
                        continue;

                    for (int k = 0; k < this->results_binary.size(); k++)
                    {
                        if (temp.size() == this->results_binary.at(k).size() && std::strcmp(temp.c_str(), this->results_binary.at(k).c_str()) == 0)
                        {
                            index = k;
                            break;
                        }
                    }

                    if (index != -1)
                    {
                        decompressed += this->results_chars.at(index);
                        i += temp.size() - 1;

                        break;
                    }
                }

                if (index == -1)
                {
                    std::cout << "INCORRECT FORMAT!";
                    return;
                }
            }

            std::cout << "decompressed: " << decompressed << '\n';

            int size = bin.size(); // 110101100

            double numerator = (double)(size / 8);
            
            if (size % 8 != 0)
                numerator++;

            double denominator = (double)decompressed.size();
            double rate = numerator * 100 / denominator;

            std::cout << "package count: " << numerator << '\n';
            std::cout << "compression rate: %" << rate << " ~= " << numerator << '/' << denominator << '\n';
        }
        void Huffman::list_results()
        {
            for (int i = 0; i < this->results_binary.size(); i++)
            {
                std::cout << this->results_binary.at(i) << ' ';
                std::cout << this->results_chars.at(i) << '\n';
            }

            std::cout << '\n';
        }
        void Huffman::list_preorder()
        {
            std::cout << "output: ";

            this->list_preorder_private(this->root);

            std::cout << '\n';
        }
    }
}