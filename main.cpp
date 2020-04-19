#include<iostream>

#include<SFML/Graphics.hpp>

#include "circuit.hpp"
#include "ui.hpp"

#include "graph.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Kirchhoff");
    window.setVerticalSyncEnabled(true);

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
                ui.handle_keyboard_inputs(e);
            }
        }

        window.clear(sf::Color::Yellow);

        ui.draw();

        window.display();
    }

    return 0;
}
