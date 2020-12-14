#include "PhysicsEngine.h"
#include <math.h>


PhysicsEngine::PhysicsEngine() : Module()
{

}

PhysicsEngine::~PhysicsEngine()
{
}

bool PhysicsEngine::Start()
{
	gravity = Vec2(0, 0.5);
	return true;
}

bool PhysicsEngine::PreUpdate()
{

	return true;
}

bool PhysicsEngine::Update(float dt)
{
	IntegerVerlet(&rocket->pos, &rocket->velocity, rocket->acceleration, dt);

	ApplyGravity();

	rocket->OnCollision();

	return true;
}

bool PhysicsEngine::PostUpdate()
{
	return true;
}

bool PhysicsEngine::CleanUp()
{
	return true;
}

void PhysicsEngine::IntegerVerlet(Vec2 *pos, Vec2 *v, Vec2 a, float dt)
{
	pos->x += v->x * dt + 0.5 * a.x * dt * dt;
	v->x += a.x * dt;

	pos->y += v->y * dt + 0.5 * a.y * dt * dt;
	v->y += a.y * dt;

}

void PhysicsEngine::ApplyGravity()
{
	/*ListItem<Body*> *item = bodyList.start;

	while (item != nullptr)
	{
		
		item->data->velocity += gravity;

		item = item->next;
	}*/

	rocket->velocity += gravity;
}

Vec2 PhysicsEngine::forceGrav(float gravity, float mass1, float mass2, float distance, Vec2 direction)
{
	Vec2 forceGravity;

	float gravityFormule = (gravity * (mass1 * mass2) / (distance * distance));

	
	forceGravity.x = direction.x * gravityFormule;
	forceGravity.y = direction.y * gravityFormule;


	return forceGravity;
}

Vec2 PhysicsEngine::forceAeroDrag(float density, float relativeVelocity, float surface, float dragCoefficient)
{
	Vec2 test;

	float aeroDragFormule = 0.5 * density * surface * dragCoefficient;

	return test;
}

Vec2 PhysicsEngine::forceAeroLift()
{
	Vec2 test;
	return test;
}

Vec2 PhysicsEngine::forceHydroBuoy()
{
	Vec2 test;
	return test;
}

Vec2 PhysicsEngine::forceHydroDrag()
{
	Vec2 test;
	return test;
}

Rocket* PhysicsEngine::CreateRocket(Vec2 position, float mass, Vec2 velocity, float rad, int health, float fuel)
{
	Rocket *rocket = new Rocket();
	rocket->pos = position;
	rocket->mass = mass;
	rocket->velocity = velocity;
	rocket->health = health;
	rocket->fuel = fuel;
	rocket->radius = rad;
	
	bodyList.Add(rocket);

	return rocket;
}

Planet* PhysicsEngine::CreatePlanet(Vec2 position, float mass, float rad)
{
	Planet* earth = new Planet();
	earth->pos = position;
	earth->mass = mass;
	earth->radius = rad;

	bodyList.Add(earth);

	return earth;
}