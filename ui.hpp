#pragma once

#include<vector>

#include<SFML/Graphics.hpp>

#include "circuit.hpp"
#include "ui_graphics.hpp"

class UI
{
    public:
        UI(Circuit& c, sf::RenderWindow& w);
        ~UI();

        void handle_mouse_clicks();
        std::vector<sf::RectangleShape> get_shapes();
    private:
        Circuit circuit;
        sf::RenderWindow& window;
        UIGraphics ui_graphics;

        sf::Vector2i get_mouse_position();

        void select_node(Node n);
        NodeType node_type_mode();
        NodeType next_node;
        bool is_node_selected;
        Node selected_node;

        /* Taille des éléments et des arcs */
        sf::Vector2f node_size;
        float line_width;
};
