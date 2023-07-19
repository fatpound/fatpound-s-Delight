#pragma once

#include "fatpound.hpp"

namespace fatpound::compression
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

            char k = '\0';

            char trash0 = '\0'; // to avoid C4820
            char trash1 = '\0';
            char trash2 = '\0';
            char trash3 = '\0';
            char trash4 = '\0';
            char trash5 = '\0';
            char trash6 = '\0';

            std::int64_t num = 0;

            ~node();
            node(std::int64_t new_num, char new_k);
            node(Huffman::node* sol, Huffman::node* sag);
        };

        std::vector<char>        results_chars;
        std::vector<std::string> results_binary;

        Huffman::node* root = nullptr;

        std::size_t node_count = 0;
        std::size_t leaf_count = 0;

        std::size_t min_depth = UINT64_MAX;
        std::size_t max_depth = 0;

        void set_binary_values_private(Huffman::node* node, std::string str);
        void list_preorder_private(Huffman::node* node) const;


    protected:


    public:
        void decompress(std::string& bin);

        void list_preorder() const;
        void list_results() const;

        ~Huffman();
        Huffman(std::string input);
    };


    Huffman::node::~node()
    {

    }
    Huffman::node::node(std::int64_t new_num, char new_k)
    {
        this->num = new_num;
        this->k = new_k;
    }
    Huffman::node::node(Huffman::node* sol, Huffman::node* sag)
    {
        this->k     = '\0';
        this->num   = sol->num + sag->num;

        this->left  = sol;
        this->right = sag;
    }

    Huffman::~Huffman()
    {

    }
    Huffman::Huffman(std::string input)
    {
        std::vector<std::pair<std::int64_t, char>> pairs;

        for (auto x : input)
        {
            std::int64_t index = -1;

            for (std::size_t i = 0; i < pairs.size(); i++)
                if (pairs.at(i).second == x)
                    index = (std::int64_t)i;

            if (index == -1)
                pairs.push_back(std::pair<std::size_t, char>{1, x});
            else
                pairs.at((const std::size_t)index).first++;
        }

        std::sort(pairs.begin(), pairs.end());

        std::deque<Huffman::node*> deque;

        for (std::size_t i = 0; i < pairs.size(); i++)
            deque.push_back(new node(pairs.at(i).first, pairs.at(i).second));

        const std::size_t first_size = deque.size();

        for (std::size_t i = 0; i < first_size - 1; i++)
        {
            Huffman::node* sol = deque.at(0);
            Huffman::node* sag = deque.at(1);

            Huffman::node* yeni_dugum = new Huffman::node(sol, sag);

            deque.pop_front();
            deque.pop_front();

            std::size_t index = 0;

            for (std::size_t j = 0; j < deque.size(); j++)
            {
                if (yeni_dugum->num > deque.at(index)->num)
                {
                    index = j + 1;
                }
                else break;
            }
            
            deque.insert(deque.begin() + (std::int64_t)index, yeni_dugum);
        }

        this->root = deque.at(0);
        this->node_count = first_size * 2 - 1;

        this->set_binary_values_private(this->root, "");

        std::cout << "min_depth: " << this->min_depth << '\n'
                  << "max_depth: " << this->max_depth << '\n';
    }

    void Huffman::set_binary_values_private(Huffman::node* node, std::string str)
    {
        if (node == nullptr)
            return;

        if (node->left == nullptr && node->right == nullptr)
        {
            this->results_chars.push_back(node->k);
            this->results_binary.push_back(str);
            
            if (this->max_depth < str.size())
                this->max_depth = str.size();
            
            if (this->min_depth > str.size())
                this->min_depth = str.size();

            return;
        }

        this->set_binary_values_private(node->left, str + "0");
        this->set_binary_values_private(node->right, str + "1");
    }
    void Huffman::list_preorder_private(Huffman::node* node) const
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

    void Huffman::decompress(std::string& bin)
    {
        std::string decompressed = "";

        for (std::size_t i = 0; i < bin.size(); i++)
        {
            std::string temp = "";

            std::int64_t index = -1;

            for (std::size_t j = i; j < bin.size() && temp.size() <= this->max_depth; j++)
            {
                temp += bin.at(j);

                if (temp.size() < this->min_depth)
                    continue;

                for (std::size_t k = 0; k < this->results_binary.size(); k++)
                {
                    if (temp.size() == this->results_binary.at(k).size() && std::strcmp(temp.c_str(), this->results_binary.at(k).c_str()) == 0)
                    {
                        index = (std::int64_t)k;

                        break;
                    }
                }

                if (index != -1)
                {
                    decompressed += this->results_chars.at((const std::size_t)index);
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

        std::size_t size = bin.size();

        double numerator = (double)(size / 8);
        
        if (size % 8 != 0)
            numerator++;

        double denominator = (double)decompressed.size();
        double rate = numerator * 100 / denominator;

        std::cout << "package count: " << numerator << '\n';
        std::cout << "compression rate: %" << rate << " ~= " << numerator << '/' << denominator << '\n';
    }
    void Huffman::list_results() const
    {
        for (std::size_t i = 0; i < this->results_binary.size(); i++)
        {
            std::cout << this->results_binary.at(i) << ' '
                      << this->results_chars.at(i) << '\n';
        }

        std::cout << '\n';
    }
    void Huffman::list_preorder() const
    {
        std::cout << "output: ";

        this->list_preorder_private(this->root);

        std::cout << '\n';
    }
}