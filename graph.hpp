#pragma once

#include<vector>

#include<eigen3/Eigen/Core>

typedef Eigen::MatrixXi GraphMatrix; // Ce nom là est plus nice quand même :) On assume aussi que ce sont des matrices carrées

class Graph
{
    public:
        static bool is_graph_antisymmetric(GraphMatrix matrix_graph);
        static GraphMatrix get_comatrix(GraphMatrix matrix_graph);
        static GraphMatrix get_spanning_tree(GraphMatrix matrix_graph);
        static std::vector<GraphMatrix> get_fundamental_set_of_cycles(GraphMatrix a);
        static std::vector<GraphMatrix> orient_cycles(std::vector<GraphMatrix> cycles);
        static GraphMatrix prune(GraphMatrix matrix_graph);
    private:
        Graph(); // Static class
};
