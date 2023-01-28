/**
 * @file        test_graph.cpp
 * 
 * @brief       Sample application for testing the tree-graph data structure.
 * 
 * @author      Filippo Maggioli\n
 *              (maggioli@di.uniroma1.it, maggioli.filippo@gmail.com)\n
 *              Sapienza, University of Rome - Department of Computer Science
 * 
 * @date        2023-01-28
 */
#include <pwd/pwd.hpp>


int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        std::cerr << "This executable needs an input graph file." << std::endl;
        exit(-1);
    }

    std::string GraphFile = argv[1];
    pwd::Graph Graph(GraphFile);
    


    return 0;
}