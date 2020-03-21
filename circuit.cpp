#include "circuit.hpp"

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

void Circuit::remove_node(unsigned int index)
{
    nodes.erase(nodes.begin()+index);
}

void Circuit::remove_arrow(unsigned int index)
{
    arrows.erase(arrows.begin()+index);
}

const std::vector<Node>& Circuit::get_nodes() const
{
    return nodes;
}

const std::vector<Arrow>& Circuit::get_arrows() const
{
    return arrows;
}

unsigned int Circuit::get_node_index(Node n) const
{
    std::vector<Node>::const_iterator it;
    it = std::find(nodes.begin(), nodes.end(), n);

    return it - nodes.begin();
}

void Circuit::set_node_value(unsigned int index, int value)
{
    nodes[index].value = value;
}

GraphMatrix Circuit::get_adjacency_matrix() const
{
    int n = nodes.size();
    GraphMatrix m(n, n);
    m.fill(0);

    for(Arrow arrow : arrows)
    {
        std::vector<Node>::const_iterator it;
        int row, col;

        row = get_node_index(arrow.a);
        col = get_node_index(arrow.b);

        m(row, col) = 1;
    }

    return m;
}
