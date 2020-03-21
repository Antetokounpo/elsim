#pragma once

#include<vector>
#include<string>

#include<SFML/Graphics.hpp>

#include "circuit.hpp"
#include "ui_graphics.hpp"

enum class UIStates
{
    NORMAL,
    TEXT_INPUT
};

class UI
{
    public:
        UI(Circuit& c, sf::RenderWindow& w);
        ~UI();

        void handle_mouse_clicks();
        void handle_keyboard_inputs(sf::Event e);
        void draw();
    private:
        Circuit& circuit;
        sf::RenderWindow& window;
        UIGraphics ui_graphics;

        UIStates current_state;

        sf::Vector2i get_mouse_position();

        void select_node(Node n);
        void delete_selected_node();
        void set_node_value(int value);
        NodeType node_type_mode();
        NodeType next_node;
        bool is_node_selected;
        Node selected_node;

        /* Esthétique */
        sf::Font font;
        std::string input_value;
};
