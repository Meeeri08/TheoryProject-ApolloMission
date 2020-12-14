#include "Rocket.h"
#include "PhysicsEngine.h"



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