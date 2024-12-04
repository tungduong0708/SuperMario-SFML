#pragma once
#include"Renderer.h"

#include<vector>
#include<SFML/Graphics.hpp>

class Map
{
private:
public:
    float cellSize;
    std::vector<std::vector<int>> grid;

    Map(float cellSize = 1.0f);

    void CreateCheckerBoard(size_t width, size_t height);
    sf::Vector2f CreateFromImage(const sf::Image& image);

    void Draw(Renderer& renderer);
};