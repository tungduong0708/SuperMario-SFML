#pragma once
#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>

class Resources
{
private:

public:
    static std::unordered_map<std::string, sf::Texture> textures;
    Resources();
    ~Resources();
};