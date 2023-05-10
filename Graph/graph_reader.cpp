#include "graph_reader.h"

graph_reader::graph_reader()
{

}
graph_reader::~graph_reader()
{

}
graph_reader::graph_reader(std::string str)
{
    this->filename = str;

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

        this->adj_matrix.push_back(vec);
    }

    my_file.close();
}