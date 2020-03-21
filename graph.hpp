#pragma once

#include<eigen3/Eigen/Core>

typedef Eigen::MatrixXi GraphMatrix; // Ce nom là est plus nice quand même :)

class Graph
{
    public:
        static bool is_graph_antisymmetric(GraphMatrix matrix_graph);
    private:
        static GraphMatrix get_comatrix(GraphMatrix matrix_graph);
        Graph(); // Static class
};
