#pragma once

#include<eigen3/Eigen/Core>

typedef Eigen::MatrixXi GraphMatrix; // Ce nom là est plus nice quand même :) On assume aussi que ce sont des matrices carrées

class Graph
{
    public:
        static bool is_graph_antisymmetric(GraphMatrix matrix_graph);
        static int count_cycles(GraphMatrix matrix_graph);
        static GraphMatrix get_comatrix(GraphMatrix matrix_graph);
        static GraphMatrix get_spanning_tree(GraphMatrix matrix_graph);
        Graph(); // Static class
};
