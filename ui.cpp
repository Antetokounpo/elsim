#include "ui.hpp"

#include<vector>
#include<cmath>

#include<SFML/Graphics.hpp>

#include "circuit.hpp"

UI::UI(Circuit& c, sf::RenderWindow& w) : circuit(c), window(w)
{
    is_node_selected = false;
    node_size = {20, 20};
    line_width = 5;
    next_node = NO_TYPE_NODE;
}

UI::~UI(){}

sf::Vector2i UI::get_mouse_position()
{
    return sf::Mouse::getPosition(window);
}

void UI::select_node(Node n)
{
    selected_node = n;
    is_node_selected = true;
}

NodeType UI::node_type_mode()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        return NEG_RESISTOR;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        return NEG_SOURCE;
    else
        return NO_TYPE_NODE;
}

void UI::handle_mouse_clicks()
{

    NodeType current_type_mode;
    if(next_node == NO_TYPE_NODE) // S'il y a une prochaine node de set, on la select, sinon on se fie au clavier
        current_type_mode = node_type_mode();
    else
        current_type_mode = next_node;

    sf::Vector2i mouse_position = get_mouse_position();
    int x = mouse_position.x;
    int y = mouse_position.y;

    for(const Node& n: circuit.get_nodes()) // Check si on n'essaye pas de sélectionner une node existante
    {
        if(ui_graphics.check_collision(n, x , y))
        {
            if(is_node_selected) // S'il y a déjà une node sélectionnée, on crée un nouvel arc
            {
                // On permet seulement de faire avec le lien avec une node existante, si la node selectionnée n'a pas de type ou si c'est la borne positive
                // de l'élément, car on veut empêcher la création d'élément polaire "cassé"
                if(current_type_mode % 2 || current_type_mode == NO_TYPE_NODE)
                {
                    circuit.add_arrow(selected_node, n);
                    is_node_selected = false;
                }
                return;
            }
            select_node(n); // Sinon on sélectionne la node pointée
            return;
        }
    }

    if(is_node_selected) // S'il y avait déjà une node sélectionnée, on en ajoute une nouvelle et on crée un arc entre cette dernière et la sélectionnée
    {
        circuit.add_node(x, y, current_type_mode);
        circuit.add_arrow(selected_node, circuit.get_nodes().back());
        if(current_type_mode % 2) // Ça veut dire que l'élément a une polarité
        {
            select_node(circuit.get_nodes().back());
        }
        else
            is_node_selected = false;
    }
    else // Sinon on ajoute un nouvel élément et on le select
    {
        circuit.add_node(x, y, current_type_mode);
        select_node(circuit.get_nodes().back());
    }

    if(current_type_mode % 2) // Si l'enum est impair, la borne négative de l'élément vient d'être ajoutée, donc la prochaine node va être son positif
        next_node = NodeType(current_type_mode + 1);
    else
        next_node = NO_TYPE_NODE;
}

std::vector<sf::RectangleShape> UI::get_shapes()
{
    std::vector<sf::RectangleShape> shapes;
    for(const Arrow& a: circuit.get_arrows()) // Les arcs en premier, car on veut qu'ils apparaissent en-dessous des nodes 
    {
        shapes.push_back(ui_graphics.get_visual_arrow(a));
    }

    if(is_node_selected) // On dessine une preview du prochain arc
    {
        sf::Vector2i mouse_position = get_mouse_position();
        sf::RectangleShape current_arrow = ui_graphics.get_visual_arrow({selected_node, {mouse_position.x, mouse_position.y}});
        current_arrow.setFillColor(sf::Color::White);
        
        shapes.push_back(current_arrow);
    }

    for(const Node& n: circuit.get_nodes())
    {
        shapes.push_back(ui_graphics.get_visual_node(n));
    }

    return shapes;
}
