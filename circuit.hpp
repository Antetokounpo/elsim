#pragma once

#include<vector>

#include "graph.hpp"

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
    NodeType type;
    float value;

    friend bool operator==(const Node&, const Node&);
};

struct Arrow
{
    Node a;
    Node b;

    friend bool operator==(const Arrow&, const Arrow&);
};

class Circuit
{
    public:
        Circuit();
        ~Circuit();

        void add_node(int x, int y, NodeType type);
        void add_arrow(Node a, Node b);

        void remove_node(unsigned int index);
        void remove_arrow(unsigned int index);

        const std::vector<Node>& get_nodes() const;
        const std::vector<Arrow>& get_arrows() const;

        void set_node_value(unsigned int index, int value);

        unsigned int get_node_index(Node n) const;
        unsigned int get_arrow_index(Arrow a) const;

        GraphMatrix get_adjacency_matrix() const;
    private:
        std::vector<Node> nodes;
        std::vector<Arrow> arrows;
};

/*
    TEMPORAIRE
    Les caractéristiques d'un graphe représentant un circuit électrique sont:
        - Anti-symétrique
        - Connexe
*/