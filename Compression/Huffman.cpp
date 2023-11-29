#include "Huffman.hpp"

namespace fatpound::compression
{
    Huffman::~Huffman() noexcept
    {
        Delete(root);
    }

    Huffman::Huffman(const std::string& input)
    {
        std::vector<std::pair<int64_t, char>*> pairs;

        for (auto x : input)
        {
            int64_t index = -1;

            for (size_t i = 0; i < pairs.size(); ++i)
            {
                if (pairs[i]->second == x)
                {
                    index = (int64_t)i;
                }
            }

            if (index == -1)
            {
                pairs.push_back(new std::pair<int64_t, char>{ 1LL, x });
            }
            else
            {
                pairs.at((const size_t)index)->first++;
            }
        }

        std::sort(pairs.begin(), pairs.end(), [](std::pair<int64_t, char>* ref1, std::pair<int64_t, char>* ref2) {return ref1->first < ref2->first; });

        std::deque<Huffman::node*> deque;

        for (size_t i = 0; i < pairs.size(); ++i)
        {
            deque.push_back(new Huffman::node{ pairs[i]->first, pairs[i]->second });
        }

        const size_t first_size = deque.size();

        for (size_t i = 0; i < first_size - 1; ++i)
        {
            Huffman::node* sol = deque[0];
            Huffman::node* sag = deque[1];

            Huffman::node* yeni_dugum = new Huffman::node(sol, sag);

            deque.pop_front();
            deque.pop_front();

            size_t index = 0;

            for (size_t j = 0; j < deque.size(); ++j)
            {
                if (yeni_dugum->num > deque[index]->num)
                {
                    index = j + 1;
                }
                else
                {
                    break;
                }
            }

            deque.insert(deque.begin() + (int64_t)index, yeni_dugum);
        }

        root = deque[0];
        node_count = first_size * 2 - 1;

        SetBinaryValues(root, "");

        for (auto x : pairs)
        {
            delete x;
        }
    }

    void Huffman::DeCompress(std::string& bin)
    {
        std::string decompressed;

        for (size_t i = 0; i < bin.size(); ++i)
        {
            std::string temp = "";

            int64_t index = -1;

            for (size_t j = i; j < bin.size() && temp.size() <= max_depth; ++j)
            {
                temp += bin[j];

                if (temp.size() < min_depth)
                {
                    continue;
                }

                for (size_t k = 0; k < results_binary.size(); ++k)
                {
                    if (temp.size() == results_binary[k].size() && std::strcmp(temp.c_str(), results_binary[k].c_str()) == 0)
                    {
                        index = (int64_t)k;

                        break;
                    }
                }

                if (index != -1)
                {
                    decompressed += results_chars.at((const size_t)index);
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

        size_t size = bin.size();

        double numerator = (double)(size / 8);

        if (size % 8 != 0)
        {
            ++numerator;
        }

        double denominator = (double)decompressed.size();
        double rate = numerator * 100 / denominator;

        std::cout << "package count: " << numerator << '\n';
        std::cout << "compression rate: %" << rate << " ~= " << numerator << '/' << denominator << '\n';
    }
    void Huffman::ListPreorder() const
    {
        std::cout << "output: ";

        ListPreorder(root);

        std::cout << '\n';
    }
    void Huffman::ListResults()  const
    {
        std::cout << "min_depth: " << min_depth << '\n'
                  << "max_depth: " << max_depth << '\n';

        for (size_t i = 0; i < results_binary.size(); ++i)
        {
            std::cout << results_binary[i] << ' '
                      << results_chars[i] << '\n';
        }

        std::cout << '\n';
    }

    void Huffman::Delete(node* node)
    {
        if (node == nullptr)
        {
            return;
        }

        Delete(node->left);
        Delete(node->right);

        delete node;
    }
    void Huffman::SetBinaryValues(node* node, const std::string& str)
    {
        if (node == nullptr)
        {
            return;
        }

        if (node->left == nullptr && node->right == nullptr)
        {
            results_chars.push_back(node->k);
            results_binary.push_back(str);

            if (max_depth < str.size())
            {
                max_depth = str.size();
            }

            if (min_depth > str.size())
            {
                min_depth = str.size();
            }

            return;
        }

        SetBinaryValues(node->left, str + "0");
        SetBinaryValues(node->right, str + "1");
    }
    void Huffman::ListPreorder(node* node) const
    {
        if (node == nullptr)
        {
            return;
        }

        if (node->left == nullptr && node->right == nullptr)
        {
            std::cout << node->k << '*' << node->num << ' ';
            return;
        }

        std::cout << node->num << ' ';

        ListPreorder(node->left);
        ListPreorder(node->right);
    }
}