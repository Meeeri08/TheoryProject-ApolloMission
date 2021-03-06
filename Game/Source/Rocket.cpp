#include "Rocket.h"
#include "PhysicsEngine.h"
#include "Module.h"

#include "Defs.h"
#include "Log.h"

Rocket::~Rocket()
{
}

void Rocket::launchRocket()
{

}


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



	if (angleRotation >= 0 && angleRotation < 90)
	{
		if (angleRotation != 0)
		{
			velocityX = (xV + angleRotation / mass) * 0.003;
		}
		else {
			velocityX = 0;
		}
		velocityY = (yV / mass + (-90 + angleRotation)) * 0.003;

	}
	else if (angleRotation < 0 && angleRotation >= -90)
	{
		velocityX = -((xV - angleRotation / mass) * 0.003);
		velocityY = -(yV / mass+(90+angleRotation))*0.003;
	}
	else if (angleRotation >= 90 && (angleRotation <= 180))
	{
		if (angleRotation != 180)
		{
			velocityX = (xV + angleRotation / mass) * 0.003;
		}
		else {
			velocityX = 0;
		}
		velocityY = (yV / mass+(-90 + angleRotation))*0.003;
	}
	else if (angleRotation < -90 && angleRotation >= -180)
	{
		if (angleRotation != -180)
		{
			velocityX = -((xV - angleRotation / mass) * 0.003);
		}
		else
		{
			velocityX = 0;
		}
		velocityY = -(yV / mass + (90 + angleRotation)) * 0.003;
	}



	
	velocity.x += velocityX;
	
	if (velocity.y > limitVelocityDown)
	{
		velocity.y = limitVelocityDown-100;
	}else if(velocity.y < limitVelocityUp)
	{
		velocity.y = limitVelocityUp+100;
	}
	else {
		velocity.y += velocityY;
	}
		

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