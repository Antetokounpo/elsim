#include "circuit.hpp"

#include<iostream> // debug
#include<cassert> // debug


bool operator==(const Node& lhs, const Node& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}


Circuit::Circuit(){}

Circuit::~Circuit(){}

void Circuit::add_node(int x, int y, NodeType type)
{
    nodes.push_back({x, y, type});
}

void Circuit::add_arrow(Node a, Node b)
{
    arrows.push_back({a, b});
}

const std::vector<Node>& Circuit::get_nodes() const
{
    return nodes;
}

const std::vector<Arrow>& Circuit::get_arrows() const
{
    return arrows;
}

Eigen::MatrixXi Circuit::get_adjacency_matrix() const
{
    int n = nodes.size();
    Eigen::MatrixXi m(n, n);
    m.fill(0);

    for(Arrow arrow : arrows)
    {
        std::vector<Node>::const_iterator it;
        int row, col;

        it = std::find(nodes.begin(), nodes.end(), arrow.a) ;
        row = it - nodes.begin();

        it = std::find(nodes.begin(), nodes.end(), arrow.b);
        col = it - nodes.begin();

        m(row, col) = 1;
    }

    return m;
}
