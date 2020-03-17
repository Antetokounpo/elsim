#include<iostream>

#include<SFML/Graphics.hpp>

#include "circuit.hpp"
#include "ui.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Kirchhoff");
    
    Circuit circuit;
    UI ui(circuit, window);

    while(window.isOpen())
    {
        sf::Event e;
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed)
                window.close();
            else if(e.type == sf::Event::MouseButtonPressed)
            {
                if(e.mouseButton.button == sf::Mouse::Left)
                {
                    ui.handle_mouse_clicks();
                }
            }
            else if(e.type == sf::Event::KeyPressed)
            {
                if(e.key.code == sf::Keyboard::Enter)
                {
                    std::cout << circuit.get_adjacency_matrix() << std::endl;
                }
            }
        }

        window.clear(sf::Color::Yellow);

        std::vector<sf::RectangleShape> drawable_shapes = ui.get_shapes();

        for(sf::RectangleShape& shape: drawable_shapes)
            window.draw(shape);

        window.display();
    }

    return 0;
}