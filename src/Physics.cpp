#include "Physics.h"

#include<box2d/b2_draw.h>
#include<box2d/b2_world_callbacks.h>
#include<box2d/b2_contact.h>
#include<iostream>

b2World Physics::world{b2Vec2(0.0f, 9.8f)};
MyDebugDraw* Physics::debugDraw{};

class MyDebugDraw : public b2Draw
{
private:
    sf::RenderTarget& target;
public:
    MyDebugDraw(sf::RenderTarget& target) : target(target) {}
    ~MyDebugDraw(){}

    virtual void DrawCircle (const b2Vec2 &center, float radius, const b2Color &color) override {
        sf::CircleShape circle(radius);
        circle.setPosition(center.x, center.y);
        circle.setOrigin(radius, radius);
        // circle.setFillColor(sf::Color::Transparent);
        circle.setFillColor(sf::Color(255, 0, 0, 255));
        circle.setOutlineThickness(0.02f);
        circle.setOutlineColor(sf::Color((sf::Uint8)(color.r)*255, (sf::Uint8)(color.g)*255, (sf::Uint8)(color.b)*255, (sf::Uint8)(color.a)*80));
        target.draw(circle);
    }
    virtual void DrawPoint (const b2Vec2 &p, float size, const b2Color &color) override {
        sf::CircleShape circle(size);
        circle.setPosition(p.x, p.y);
        circle.setOrigin(size, size);
        // circle.setFillColor(sf::Color((sf::Uint8)(color.r)*255, (sf::Uint8)(color.g)*255, (sf::Uint8)(color.b)*255, (sf::Uint8)(color.a)*80));
        circle.setFillColor(sf::Color(255, 0, 0, 255));
        target.draw(circle);
    }
    virtual void DrawPolygon (const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) override {
        sf::ConvexShape shape(vertexCount);
        for(size_t i=0; i<vertexCount; i++) {
            shape.setPoint(i, sf::Vector2f(vertices[i].x, vertices[i].y));
        }
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineThickness(0.02f);
        shape.setOutlineColor(sf::Color((sf::Uint8)(color.r)*255, (sf::Uint8)(color.g)*255, (sf::Uint8)(color.b)*255, (sf::Uint8)(color.a)*80));
        target.draw(shape);
    }
    virtual void DrawSegment (const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) override {
        sf::VertexArray va(sf::Lines, 2);
        sf::Color sfColor = sf::Color((sf::Uint8)(color.r)*255, (sf::Uint8)(color.g)*255, (sf::Uint8)(color.b)*255, (sf::Uint8)(color.a)*80);

        va[0].position = sf::Vector2f(p1.x, p1.y);
        va[0].color = sfColor;

        va[1].position = sf::Vector2f(p1.x, p1.y);
        va[1].color = sfColor;

        target.draw(va);
    }
    virtual void DrawSolidCircle (const b2Vec2 &center, float radius, const b2Vec2 &axis, const b2Color &color) override {
        sf::CircleShape circle(radius);
        circle.setPosition(center.x, center.y);
        circle.setOrigin(radius, radius);
        // circle.setFillColor(sf::Color((sf::Uint8)(color.r)*255, (sf::Uint8)(color.g)*255, (sf::Uint8)(color.b)*255, (sf::Uint8)(color.a)*80));
        circle.setFillColor(sf::Color(255, 0, 0, 255));
        b2Vec2 p = center + (radius*axis);
        DrawSegment(center, p, color);
    }
    virtual void DrawSolidPolygon (const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) override {
        sf::ConvexShape shape(vertexCount);
        for(size_t i=0; i<vertexCount; i++) {
            shape.setPoint(i, sf::Vector2f(vertices[i].x, vertices[i].y));
        }
        shape.setFillColor(sf::Color((sf::Uint8)(color.r)*255, (sf::Uint8)(color.g)*255, (sf::Uint8)(color.b)*255, (sf::Uint8)(color.a)*80));
        target.draw(shape);
    }
    virtual void DrawTransform (const b2Transform &xf) override {
        b2Vec2 p = xf.p;
        b2Vec2 px = p + (0.5f*xf.q.GetXAxis());
        b2Vec2 py = p + (0.5f*xf.q.GetYAxis());

        DrawSegment(p, px, b2Color(1.0f, 0.0f, 0.0f));
        DrawSegment(p, py, b2Color(0.0f, 1.0f, 0.0f));
    }

};

class MyGlobalContactListener : public b2ContactListener 
{
    virtual void BeginContact(b2Contact* contact) override {
        ContactListener* listener = (ContactListener*) contact->GetFixtureA()->GetUserData().pointer;
        if (listener) {
            listener->OnBeginContact();
        }

        listener = (ContactListener*) contact->GetFixtureB()->GetUserData().pointer;
        if (listener) {
            listener->OnBeginContact();
        }
    }
    virtual void EndContact(b2Contact* contact) override {
        ContactListener* listener = (ContactListener*) contact->GetFixtureA()->GetUserData().pointer;
        if (listener) listener->OnEndContact();

        listener = (ContactListener*) contact->GetFixtureB()->GetUserData().pointer;
        if (listener) listener->OnEndContact();
    }
};

void Physics::Init()
{
}

void Physics::Update(float gameTime)
{
    world.Step(gameTime, 8, 4);
    world.SetContactListener(new MyGlobalContactListener());
}

void Physics::DebugDraw(Renderer &renderer)
{
    if (!debugDraw) 
    {
        debugDraw = new MyDebugDraw(renderer.target);
        debugDraw->SetFlags(b2Draw::e_shapeBit);
        world.SetDebugDraw(debugDraw);
    }
    world.DebugDraw();
}
