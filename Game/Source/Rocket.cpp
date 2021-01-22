#include "Rocket.h"
#include "PhysicsEngine.h"
#include "Module.h"

#include "Defs.h"
#include "Log.h"

Rocket::~Rocket()
{
	//idlAnim.PushBack({ 0, 0, 64, 85 });
}

void Rocket::launchRocket()
{

}
//
//bool Rocket::Awake()
//{
//	LOG("Loading Rocket");
//	bool ret = true;
//
//	return ret;
//}
//
//bool Rocket::Start()
//{
//	currentAnimation = &idlAnim;
//	return true;
//}
//
//
//bool Rocket::Update()
//{
//
//	return true;
//}
//
//bool Rocket::PostUpdate()
//{
//	SDL_Rect rect = currentAnimation->GetCurrentFrame();
//	return true;
//}


void Rocket::refillFuel()
{

}

void Rocket::AddMomentum(float xV, float yV)
{
	float velocityX = xV / mass;
	float velocityY = yV / mass;
	velocity.x += velocityX;
	velocity.y += velocityY;

}

void Rocket::AddMomentumAngle(float xV, float yV, float angleRotation)
{
	float velocityX, velocityY;
	if (angleRotation == 0)
	{
		velocityX = 0;
		velocityY = (yV / mass);
	}
	else if (angleRotation == 180 || angleRotation == -180)
	{
		velocityX = 0;
		velocityY = -(yV / mass);
	}


	else if (angleRotation > 0 && angleRotation < 90)
	{
		velocityX = (xV + angleRotation / mass) * 0.005;
		velocityY = (yV / mass+(-1/angleRotation));
	}
	else if (angleRotation < 0 && angleRotation > -90)
	{
		velocityX = -((xV - angleRotation / mass) * 0.005);
		velocityY = (yV / mass-(-1/angleRotation));
	}
	else if (angleRotation > 90 && (angleRotation < 180 || angleRotation == -180))
	{
		velocityX = (xV + angleRotation / mass) * 0.005;
		velocityY = -(yV / mass+(-1/angleRotation));
	}
	else if (angleRotation < -90 && (angleRotation > -180 || angleRotation == 180))
	{
		velocityX = -((xV - angleRotation / mass) * 0.005);
		velocityY = -(yV / mass-(-1/angleRotation));
	}
	//float velocityX = (xV+angleRotation / mass)*0.005;
	//float velocityY = (yV-angleRotation / mass)*0.05;



	velocity.x += velocityX;
	velocity.y += velocityY;

}

void Rocket::OnCollision()
{
	ListItem<Body*>* item = app->physicsEngine->bodyList.start;

	while (item != nullptr)
	{
		if (item->data != this)
		{
			if ((item->data->radius + this->radius) > (sqrt(pow(item->data->pos.x - this->pos.x, 2) + pow(item->data->pos.y - this->pos.y, 2))))
			{
				if ((this->pos.x >= item->data->pos.x) && (this->pos.y <= item->data->pos.y))
				{
					this->velocity = Vec2(10, -10);
					AddMomentum(10, -10);
				}
				else if ((this->pos.x < item->data->pos.x) && (this->pos.y < item->data->pos.y))
				{
					this->velocity = Vec2(-10, -10);
					AddMomentum(-10, -10);
				}
				else if ((this->pos.x < item->data->pos.x) && (this->pos.y > item->data->pos.y))
				{
					this->velocity = Vec2(-10, 10);
					AddMomentum(-10, 10);
				}
				else if ((this->pos.x > item->data->pos.x) && (this->pos.y > item->data->pos.y))
				{
					this->velocity = Vec2(10, 10);
					AddMomentum(10, 10);
				}
			}
		}
		item = item->next;
	}
}