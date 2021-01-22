#ifndef __ROCKET_H__
#define __ROCKET_H__

#include "Body.h"
#include "Vectors.h"
#include "Animation.h"

class Rocket : public Body
{
public:

	Rocket(){}
	~Rocket();

	//bool Awake();

	//bool Start();

	//bool Update();

	//bool PostUpdate();

	//Animation* currentAnimation = nullptr;

	//Animation idlAnim;

public:
	int health;
	float fuel;
	Vec2 velocity;
	Vec2 acceleration;
	float f;
	float angle;

public:

	void launchRocket();
	void refillFuel();
	void AddMomentum(float xV, float yV);
	void AddMomentumAngle(float xV, float yV, float angleRotation);
	void OnCollision();

};



#endif // __ROCKET_H__