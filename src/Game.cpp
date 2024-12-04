#include"Game.h"
#include"Resources.h"
#include"Map.h"
#include"Physics.h"
#include"Mario.h"

#include <filesystem>
#include <iostream>

Map map(1.0f);
Camera camera(20.0f);
Mario mario;

void Begin(const sf::Window &window)
{
    for(auto& file : std::filesystem::directory_iterator("./resources/")) 
    {
        if (file.is_regular_file() && (file.path().extension() == ".png" || file.path().extension() == ".jpg"))
        {
            Resources::textures[file.path().filename().string()].loadFromFile(file.path().string());
        }
    }
    Physics::Init();
    
    sf::Image image;
    image.loadFromFile("resources/map.png");
    sf::Vector2f pos = map.CreateFromImage(image);
    mario.position.x = pos.x;
    mario.position.y = pos.y;
    std::cout << mario.position.x << " " << mario.position.y << std::endl;
    mario.Begin();
}

void Update(float gameTime)
{   
    Physics::Update(gameTime);
    camera.position = mario.position;
    mario.Update(gameTime);
}

void Render(Renderer& renderer)
{
    map.Draw(renderer);
    mario.Draw(renderer);

    Physics::DebugDraw(renderer);
}
