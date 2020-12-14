#pragma once

#include "App.h"
#include "Module.h"
#include "Vectors.h"
#include "Rocket.h"
#include "Planet.h"
#include "Body.h"

enum class crossSection
{
    WATER = 0,
    GROUND,
    AIR,
};


class PhysicsEngine : public Module
{
public:

    PhysicsEngine();
    virtual ~PhysicsEngine();    

public:

    bool Start();
    bool PreUpdate();
    bool Update(float dt);
    bool PostUpdate();
    bool CleanUp();

public: // May the Force be with you

    Vec2 forceGrav(float gravity, float mass1, float mass2, float distance, Vec2 direction);
    Vec2 forceAeroDrag(float density, float relativeVelocity, float surface, float dragCoefficient);
    Vec2 forceAeroLift();
    Vec2 forceHydroBuoy();
    Vec2 forceHydroDrag();

	Rocket* CreateRocket(Vec2 position, float mass, Vec2 velocity, float rad, int health, float fuel);
	Planet* CreatePlanet(Vec2 position, float mass, float rad);

    void IntegerVerlet(Vec2* pos, Vec2* v, Vec2 a, float dt);

    void ApplyGravity();

    Vec2 gravity;
    Rocket *rocket;


    List<Body*> bodyList;
};