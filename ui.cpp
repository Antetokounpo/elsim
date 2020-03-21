#include "ui.hpp"

#include<vector>
#include<cmath>
#include<iostream> //temp

#include<SFML/Graphics.hpp>

#include "circuit.hpp"
#include "graph.hpp"

UI::UI(Circuit& c, sf::RenderWindow& w) : circuit(c), window(w)
{
    is_node_selected = false;
    next_node = NO_TYPE_NODE;
    current_state = UIStates::NORMAL;
    font.loadFromFile("fonts/Pixeled.ttf"); // Load font
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

void UI::set_node_value(int value)
{
    if(!is_node_selected)
        return;

    circuit.set_node_value(circuit.get_node_index(selected_node), value);
    is_node_selected = false;
}

void UI::handle_keyboard_inputs(sf::Event e)
{
    if(e.key.code == sf::Keyboard::Enter && current_state == UIStates::NORMAL)
        std::cout << Graph::is_graph_antisymmetric(circuit.get_adjacency_matrix()) << std::endl;
    else if(current_state == UIStates::NORMAL)
        return;
    else if(current_state == UIStates::TEXT_INPUT)
    {
        switch(e.key.code)
        {
            case sf::Keyboard::Num0:
                input_value += "0";
                break;
            case sf::Keyboard::Num1:
                input_value += "1";
                break;
            case sf::Keyboard::Num2:
                input_value += "2";
                break;
            case sf::Keyboard::Num3:
                input_value += "3";
                break;
            case sf::Keyboard::Num4:
                input_value += "4";
                break;
            case sf::Keyboard::Num5:
                input_value += "5";
                break;
            case sf::Keyboard::Num6:
                input_value += "6";
                break;
            case sf::Keyboard::Num7:
                input_value += "7";
                break;
            case sf::Keyboard::Num8:
                input_value += "8";
                break;
            case sf::Keyboard::Num9:
                input_value += "9";
                break;
            
            case sf::Keyboard::Backspace:
                input_value.pop_back();
                break;
            case sf::Keyboard::Enter:
                circuit.set_node_value(circuit.get_node_index(selected_node), std::stoi(input_value));
                is_node_selected = false;
                current_state = UIStates::NORMAL;
                break;
            default:
                break;
        }
    }
}

void UI::handle_mouse_clicks()
{
    if(current_state != UIStates::NORMAL)
        return;

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

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::V))
            {
                current_state = UIStates::TEXT_INPUT;
                input_value = "";
            }

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

void UI::draw()
{
    std::vector<sf::RectangleShape> shapes;
    for(const Arrow& a: circuit.get_arrows()) // Les arcs en premier, car on veut qu'ils apparaissent en-dessous des nodes 
    {
        window.draw(ui_graphics.get_visual_arrow(a));
    }

    if(is_node_selected && current_state == UIStates::NORMAL) // On dessine une preview du prochain arc, sauf si on est en mode text input
    {
        sf::Vector2i mouse_position = get_mouse_position();
        sf::RectangleShape current_arrow = ui_graphics.get_visual_arrow({selected_node, {mouse_position.x, mouse_position.y}});
        current_arrow.setFillColor(sf::Color::White);

        window.draw(current_arrow);
    }

    for(const Node& n: circuit.get_nodes())
    {
        window.draw(ui_graphics.get_visual_node(n));
    }

    if(current_state == UIStates::TEXT_INPUT)
    {
        sf::Text text;
        text.setFont(font);
        text.setFillColor(sf::Color::Black);

        text.setString("Input value: "+input_value);
        text.setCharacterSize(24);

        text.setPosition(20, 20);

        window.draw(text);
    }
}
