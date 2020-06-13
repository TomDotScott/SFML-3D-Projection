#include <iostream>
#include <SFML/Graphics.hpp>
#include "Vector3.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "C++ Snake ICA : U0018197");

    std::vector<Vector3> points
    {
        {-50, -50},
        {50, -50},
        {50, 50},
        {-50, 50}
    };
    
    float projection[2][3]
    {
        {1, 0, 0},
        {0, 1, 0}
    };

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
          switch(event.type)
          {
            case sf::Event::Closed:
              window.close();
            break;
            default:
              break;
          }
        }
        window.clear();

        //this is where the fun stuff is
        for(auto& point : points)
        {
            sf::CircleShape c(5);
        	// draw circle relative to the centre of the screen
            c.setPosition(point.m_x + static_cast<float>(window.getSize().x) / 2, point.m_y + static_cast<float>(window.getSize().y) / 2);

            window.draw(c);
        }
    	
        window.display();
    }
    return 0;
}
