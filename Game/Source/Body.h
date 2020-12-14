#pragma once
#include "Vectors.h"
#include "App.h"
#include "Module.h"

class SDL_Rect;
class Body
{

public:

	Body() {}
	~Body() {}

public:

    Vec2 pos;
    float mass;
    float radius;
   
   
    SDL_Rect *hitbox;

public:

    void AddForce(float df);
};