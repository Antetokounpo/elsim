#pragma once

#include<vector>

#include<eigen3/Eigen/Core>

enum NodeType
{
    NO_TYPE_NODE, // Gris
    NEG_SOURCE,   // Noir
    POS_SOURCE,   // Rouge
    NEG_RESISTOR, // Magenta
    POS_RESISTOR  // Cyan
};

struct Node
{
    int x;
    int y;
    unsigned int type;
    float value;

    friend bool operator==(const Node&, const Node&);
};

struct Arrow
{
    Node a;
    Node b;
};

class Circuit
{
    public:
        Circuit();
        ~Circuit();

        void add_node(int x, int y, NodeType type);
        void add_arrow(Node a, Node b);
        const std::vector<Node>& get_nodes() const;
        const std::vector<Arrow>& get_arrows() const;
        Eigen::MatrixXi get_adjacency_matrix() const;
    private:
        std::vector<Node> nodes;
        std::vector<Arrow> arrows;
};
