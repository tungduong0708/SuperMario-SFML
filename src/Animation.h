#pragma once

#include<SFML/Graphics.hpp>

struct AnimFrame    
{
    AnimFrame(float time = 0.0f, sf::Texture texture = sf::Texture()) : time(time), texture(texture){}
    float time = 0.0f;
    sf::Texture texture{};
};


class Animation
{
private:
    float time = 0.0f;
    float length;
    std::vector<AnimFrame> frames;
public:
    Animation(float length = 0.0f, std::vector<AnimFrame> frames = {}); 
    ~Animation();

    sf::Texture& GetTexture();
    void Update(float gameTime);
};


