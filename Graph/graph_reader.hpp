#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class graph_reader
{
private:


protected:


public:
    vector<vector<int>> adj_matrix;
    string filename;

    graph_reader();
    ~graph_reader();
    graph_reader(string str);
};

graph_reader::graph_reader()
{

}
graph_reader::~graph_reader()
{

}
graph_reader::graph_reader(string str)
{
    this->filename = str;

    fstream my_file;
    my_file.open(str, ios::in | ios::binary);

    while (my_file.eof() == false)
    {
        string str;
        getline(my_file, str);

        stringstream ss;
        ss << str;

        vector<int> vec;

        while (ss.eof() == false)
        {
            int x;
            ss >> x >> ws;

            vec.push_back(x);
        }

        this->adj_matrix.push_back(vec);
    }

    my_file.close();
}