#include "circuit.hpp"

bool operator==(const Node& lhs, const Node& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator==(const Arrow& lhs, const Arrow& rhs)
{
    return lhs.a == rhs.a && lhs.b == rhs.b;
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

unsigned int Circuit::get_arrow_index(Arrow a) const
{
    std::vector<Arrow>::const_iterator it;
    it = std::find(arrows.begin(), arrows.end(), a);

    return it - arrows.begin();
}

void Circuit::set_arrow_value(unsigned int index, int value, ArrowType type)
{
    arrows[index].type = type;
    arrows[index].value = value;
}

void Circuit::set_node_value(unsigned int index, float value)
{
    int node_type_offset = nodes[index].type % 2 ? 1 : -1;

    // Les deux bornes de l'élément doivent avoir la même valeur, question de logique
    nodes[index].value = value;
    nodes[index+node_type_offset].value = value;
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

        // Le graphe est non directionnel
        m(row, col) = 1;
        m(col, row) = 1;
    }

    return m;
}
