#include"Game.h"
#include"Camera.h"
#include"Renderer.h"

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 900), "SuperMario-PreBeta");
    sf::Clock gameClock;
    Renderer renderer(window);

    window.setFramerateLimit(60);
    Begin(window);
    while (window.isOpen())
    {
        float gameTime = gameClock.restart().asSeconds();
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.setView(camera.GetView(window.getSize()));
        Update(gameTime);
        
        window.clear(sf::Color::White);
        Render(renderer);
        window.display();
    }

    return 0;
}