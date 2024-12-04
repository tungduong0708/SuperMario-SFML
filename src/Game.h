#pragma once
#include"Renderer.h"
#include"Camera.h"

#include <SFML/Graphics.hpp>

extern Camera camera;

void Begin(const sf::Window &window);
void Update(float gameTime);
void Render(Renderer& renderer);