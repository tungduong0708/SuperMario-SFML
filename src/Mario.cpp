#include "Mario.h"

#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_circle_shape.h>
#include <iostream>

const float movementSpeed = 5.0f;
const float jumpVelocity = 0.7f;

void Mario::Begin()
{
    std::cout << "Initializing Mario at position: " << position.x << ", " << position.y << std::endl;
    runAnimation = Animation(0.3f, {
        AnimFrame(0.2f, Resources::textures["mario_run2.png"]),
        AnimFrame(0.1f, Resources::textures["mario_run1.png"]),
        AnimFrame(0.0f, Resources::textures["mario_run3.png"])
    });
    
    b2BodyDef bodyDef{};
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(position.x, position.y);
    bodyDef.fixedRotation = true;
    body = Physics::world.CreateBody(&bodyDef);

    if (!body) {
        std::cerr << "Failed to create Mario body!" << std::endl;
        return; 
    }

    b2FixtureDef fixtureDef{};
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;

    b2CircleShape circle{};
    circle.m_radius = 0.5f;

    circle.m_p.Set(0.0f, -0.5f);
    fixtureDef.shape = &circle;
    body->CreateFixture(&fixtureDef);

    circle.m_p.Set(0.0f, 0.5f);
    body->CreateFixture(&fixtureDef);

    b2PolygonShape polygonShape{};
    polygonShape.SetAsBox(0.5f, 0.5f);
    fixtureDef.shape = &polygonShape;
    body->CreateFixture(&fixtureDef);

    polygonShape.SetAsBox(0.4f, 0.1f, b2Vec2(0.0f, 1.0f), 0.0f);
    fixtureDef.userData.pointer = (uintptr_t)this;
    fixtureDef.isSensor = true;
    body->CreateFixture(&fixtureDef);
}

void Mario::Update(float gameTime)
{
    float move = movementSpeed;

    runAnimation.Update(gameTime);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        move *= 2;
    }

    b2Vec2 velocity = body->GetLinearVelocity();
    velocity.x = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        velocity.x += move;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        velocity.x -= move;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        velocity.y -= jumpVelocity;
    }

    textureToDraw = runAnimation.GetTexture();

    if (velocity.x < -0.02f) {
        facingLeft = true;
    }
    else if (velocity.x > 0.02f) {
        facingLeft = false;
    }
    else textureToDraw = Resources::textures["mario_stand.png"];

    if (!isGrounded) textureToDraw = Resources::textures["mario_jump.png"];

    body->SetLinearVelocity(velocity);


    position = sf::Vector2f(body->GetPosition().x, body->GetPosition().y);
    angle = body->GetAngle() * (180.0f / M_PI);
    // std::cout << position.x << " " << position.y << std::endl;
}


void Mario::Draw(Renderer &renderer)
{
    // std::cout << position.x << " " << position.y << std::endl;
    renderer.Draw(textureToDraw, position, sf::Vector2f(facingLeft ? -1.0f : 1.0f, 2.0f), angle);
}

void Mario::OnBeginContact()
{
    isGrounded++;
}

void Mario::OnEndContact()
{
    if (isGrounded>0) isGrounded--;
}
