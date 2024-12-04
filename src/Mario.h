#pragma once
#include "Renderer.h"
#include "Resources.h"
#include "Physics.h"
#include "Animation.h"

#include <SFML/Graphics.hpp>
#include <box2d/b2_body.h>

class Mario : public ContactListener
{
private:
    b2Body* body;
    size_t isGrounded = 0;
    bool facingLeft = false;
public:
    float angle;
    sf::Vector2f position;
    Animation runAnimation;
    sf::Texture textureToDraw;

    Mario() : body(nullptr), position(0.0f, 0.0f), angle(0.0f) {} 
    void Begin();
    void Update(float gameTime);
    void Draw(Renderer& renderer);

    virtual void OnBeginContact() override;
    virtual void OnEndContact() override;
};