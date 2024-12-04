#pragma once
#include "Renderer.h"

#include <box2d/b2_world.h>

class MyDebugDraw;

class ContactListener 
{
public:
    virtual void OnBeginContact() = 0;
    virtual void OnEndContact() = 0;
};

class Physics 
{
private:
public:
    static b2World world;
    static MyDebugDraw* debugDraw;

    static void Init();
    static void Update(float gameTime);
    static void DebugDraw(Renderer& renderer);
};

