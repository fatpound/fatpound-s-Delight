#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class graph_reader
{
private:


protected:


public:
    std::vector<std::vector<int>> adj_matrix;
    std::string filename;

    graph_reader();
    ~graph_reader();
    graph_reader(std::string str);
};