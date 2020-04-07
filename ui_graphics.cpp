#include "ui_graphics.hpp"

#include "ui_math.hpp"

UIGraphics::UIGraphics()
{
    // Par défaut
    node_size = {20, 20};
    line_width = 5;
}

UIGraphics::~UIGraphics(){}

void UIGraphics::set_node_size(float w, float h)
{
    node_size = {w, h};
}

void UIGraphics::set_line_width(float w)
{
    line_width = w;
}

sf::RectangleShape UIGraphics::get_visual_node(Node n)
{
    sf::RectangleShape r(node_size);
    r.setPosition(n.x, n.y);

    sf::Color node_color;
    switch (n.type)
    {
        case NEG_SOURCE:
            node_color = sf::Color::Black;
            break;
        case POS_SOURCE:
            node_color = sf::Color::Red;
            break;
        case NEG_RESISTOR:
            node_color = sf::Color::Magenta;
            break;
        case POS_RESISTOR:
            node_color = sf::Color::Cyan;
            break;
        default:
            node_color = sf::Color(128, 128, 128, 255); // Grey
            break;
    }
    r.setFillColor(node_color);

    return r;
}

sf::RectangleShape UIGraphics::get_visual_arrow(Arrow a)
{
    sf::RectangleShape r(sf::Vector2f(UIMath::distance_between_nodes(a.a, a.b), line_width));
    r.setPosition(a.a.x + node_size.x/2, a.a.y + node_size.y/2);
    r.setRotation(360.0f - UIMath::angle_between_nodes(a.a, a.b)); // On soustrait l'angle à 360°, car la rotation est clockwise
    r.setFillColor(sf::Color::Blue);

    return r;
}

bool UIGraphics::check_collision(Node n, int x, int y)
{
    sf::RectangleShape visual_node = get_visual_node(n);
    visual_node.setOrigin(node_size.x/2, node_size.y/2);
    visual_node.setScale(2.0f, 2.0f);
    return visual_node.getGlobalBounds().contains(x, y);
}
