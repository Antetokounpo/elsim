#pragma once

#include<SFML/Graphics.hpp>

#include "circuit.hpp"

class UIGraphics
{
    public:
        UIGraphics();
        ~UIGraphics();
        
        void set_node_size(float w, float h);
        void set_line_width(float w);

        sf::RectangleShape get_visual_node(Node n);
        sf::RectangleShape get_visual_arrow(Arrow a);
        sf::Text get_value_text(Node n);

        bool check_collision(Node n, int x, int y);
    private:
        sf::Vector2f node_size;
        float line_width;
};
