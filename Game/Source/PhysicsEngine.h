#pragma once

#include "App.h"
#include "Module.h"
#include "Vectors.h"
#include "Rocket.h"
#include "Planet.h"
#include "Body.h"

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

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

	Rocket* CreateRocket(Vec2 position, float mass, Vec2 velocity, float rad, int health, float fuel, float angle);
	Planet* CreatePlanet(Vec2 position, float mass, float rad);

    void IntegerVerlet(Vec2* pos, Vec2* v, Vec2 a, float dt);

    void ApplyGravity();

    Vec2 gravity;
    Vec2 gravityEarth;
    Vec2 gravityMoon;
    Rocket *rocket;

    List<Body*> bodyList;
};