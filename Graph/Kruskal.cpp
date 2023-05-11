#include "Kruskal.h"

Kruskal::Kruskal()
{

}
Kruskal::~Kruskal()
{

}
Kruskal::Kruskal(graph* graf)
{
    this->G = graf;
}

bool Kruskal::is_not_in_weighs(int value)
{
    for (int i = 0; i < this->weighs.size(); i++)
    {
        if (this->weighs.at(i) == value)
            return false;
    }

    return true;
}
bool Kruskal::is_not_in_edges(int n, int x, int y)
{
    int index = this->get_index_from_weighs(n);

    for (int j = 0; j < this->edges.at(index).size(); j++)
    {
        std::array<int, 2> arr = { 0, 0 };

        for (int k = 0; k < this->edges.at(index).at(j).size(); k++)
        {
            int n = this->edges.at(index).at(j).at(k);

            if (n == x)
                arr.at(0)++;
            else if (n == y)
                arr.at(1)++;

            if (arr.at(0) > 0 && arr.at(1) > 0)
                return false;
        }
    }

    return true;
}
bool Kruskal::available_in_result(std::vector<int> vec)
{
    for (int i = 0; i < this->result.size(); i++)
    {
        if (vec.size() <= this->result.at(i).size())
        {
            std::array<int, 2> arr = { 0, 0 };

            for (int j = 0; j < this->result.at(i).size(); j++)
            {
                int n = this->result.at(i).at(j);

                if (n == vec.at(0))
                    arr.at(0)++;
                else if (n == vec.at(1))
                    arr.at(1)++;

                if (arr.at(0) > 0 && arr.at(1) > 0)
                    return false;
            }
        }
    }

    return true;
}

int Kruskal::get_index_from_weighs(int value)
{
    for (int i = 0; i < this->weighs.size(); i++)
    {
        if (this->weighs.at(i) == value)
            return i;
    }

    return -1;
}
int Kruskal::get_index_from_result(int value)
{
    for (int i = 0; i < this->result.size(); i++)
    {
        for (int j = 0; j < this->result.at(i).size(); j++)
        {
            if (this->result.at(i).at(j) == value)
            {
                return i;
            }
        }
    }

    return -1;
}

void Kruskal::set_result(std::vector<int> vec)
{
    int index_1 = this->get_index_from_result(vec.at(0)); // index of 'g'
    int index_2 = this->get_index_from_result(vec.at(1)); // index of 'h'

    if (index_1 < 0 || index_2 < 0)
        return;

    if (this->result.at(index_1).size() >= this->result.at(index_2).size())
    {
        for (int k = 0; k < this->result.at(index_2).size(); k++)
        {
            this->result.at(index_1).push_back(this->result.at(index_2).at(k));
            this->result.at(index_2).at(k) = -1; // erasing
        }

        this->last = index_1;
        return;
    }

    if (this->result.at(index_2).size() >= this->result.at(index_1).size())
    {
        for (int k = 0; k < this->result.at(index_1).size(); k++)
        {
            this->result.at(index_2).push_back(this->result.at(index_1).at(k));
            this->result.at(index_1).at(k) = -1; // erasing
        }

        this->last = index_2;
        return;
    }
}
void Kruskal::set_different_weighs()
{
    for (int i = 0; i < this->G->adj.size(); i++)
    {
        for (int j = 0; j < this->G->adj.at(i).size(); j++)
        {
            int n = this->G->adj.at(i).at(j);

            if (n != 0 && is_not_in_weighs(n))
            {
                this->weighs.push_back(n);
                this->weighs_counts.push_back(0);
            }
        }
    }

    sort(this->weighs.begin(), this->weighs.end());
    this->edges.resize(this->weighs.size());

    for (int i = 0; i < this->G->adj.size(); i++)
    {
        for (int j = 0; j < this->G->adj.at(i).size(); j++)
        {
            int n = this->G->adj.at(i).at(j);

            if (n != 0 && this->is_not_in_edges(n, i, j))
            {
                this->weighs_counts.at(this->get_index_from_weighs(n))++;

                std::vector<int> v;

                v.push_back(i);
                v.push_back(j);

                this->edges.at(this->get_index_from_weighs(n)).push_back(v);
            }
        }
    }

    for (int i = 0; i < this->weighs_counts.size(); i++)
    {
        this->weighs_counts.at(i) /= 2;
    }
}

void Kruskal::run()
{
    this->set_different_weighs();

    this->result.resize(this->G->edge_count);

    for (int i = 0; i < this->result.size(); i++)
    {
        std::vector<int> v;

        v.push_back(i);

        this->result.at(i) = v;
    }

    for (int i = 0; i < this->edges.size(); i++)
    {
        for (int j = 0; j < this->edges.at(i).size(); j++)
        {
            if (available_in_result(this->edges.at(i).at(j)))
            {
                this->set_result(this->edges.at(i).at(j));
            }
        }
    }
    for (int i = 0; i < this->result.at(this->last).size(); i++)
    {
        std::cout << "abcdefghijk"[this->result.at(this->last).at(i)];
    }

    std::cout << '\n';
}