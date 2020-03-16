#include "circuit.hpp"

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
