#include "circuit.hpp"

#include<eigen3/Eigen/LU>
#include<iostream> // temp

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
        int row = get_node_index(arrow.a);
        int col = get_node_index(arrow.b);

        // Le graphe est non directionnel
        m(row, col) = 1;
        m(col, row) = 1;
    }

    return m;
}

std::vector<unsigned int> Circuit::cycle_to_node_list(GraphMatrix cycle)
{
    int n = cycle.rows();
    
    std::vector<unsigned int> adjency_list;
    for(int i = 0; i<n; ++i)
    {
        for(int j = 0; j<n; ++j)
        {
            if(cycle(i, j))
            {
                adjency_list.push_back(i);
                adjency_list.push_back(j);
            }
        }
    }

    return adjency_list;
}

void Circuit::kirchoff_law(std::vector<GraphMatrix> loops)
{
    const int n = loops.size();
    Eigen::MatrixXf resistances(n, n);
    resistances.fill(0.0);
    Eigen::VectorXf voltages(n);
    voltages.fill(0.0);

    for(unsigned int l = 0; l<loops.size(); ++l)
    {
        for(unsigned int k = 0; k<loops.size(); ++k)
        {
            const GraphMatrix current_loop = loops[l] + loops[k];
            const int m = current_loop.rows();

            for(int i = 0; i<m; ++i)
            {
                for(int j = 0; j<m; ++j)
            {
                    if(current_loop(i, j) != 2)
                        continue;

                    // Si une des deux nodes n'a pas de type, le lien entre eux est insignifiant
                    if(!(nodes[i].type && nodes[j].type))
                        continue;

                    int type_offset = nodes[i].type % 2 ? 1 : -1;

                    if(nodes[i].type+type_offset == nodes[j].type && i == j-type_offset)
                    {
                        switch(nodes[i].type)
                        {
                            case NEG_RESISTOR:
                            case POS_RESISTOR:
                                resistances(l, k) += nodes[i].value;
                                break;
                            case NEG_SOURCE:
                                voltages(l) += nodes[i].value;
                                break;
                            case POS_SOURCE:
                                voltages(l) -= nodes[i].value;
                                break;
                            default:
                                break;
                        }

                        if(k != l)
                            resistances(l, k) = -resistances(l, k);
                    }
                }
            }
        }
    }

    std::cout << resistances << std::endl;
    std::cout << voltages << std::endl;
    std::cout << resistances.inverse() * voltages << std::endl;
}
