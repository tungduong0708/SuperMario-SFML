#pragma once
#include <SFML/Graphics.hpp>

class Renderer {
private:
    sf::Sprite sprite;
public:
    sf::RenderTarget& target;

    Renderer(sf::RenderTarget& target);
    void Draw(sf::Texture &texture, const sf::Vector2f &position, const sf::Vector2f &size, float angle = 0.0f);
};