#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Rocket.h"
#include "Planet.h"

#include "Defs.h"


struct SDL_Texture;
class SDL_Rect;


class Scene : public Module
{
public:

	Scene();

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	bool Restart();

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();
	bool HalfCleanUp();

private:
	SDL_Texture* background;
	SDL_Texture* texRocket;
	SDL_Texture* texRocketUp;
	SDL_Texture* texWin;
	SDL_Texture* texLose;
	SDL_Texture* texIntro;
	SDL_Texture* texTrampoline;
	SDL_Texture* texFullFuel;
	SDL_Texture* texThreeFuel;
	SDL_Texture* texTwoFuel;
	SDL_Texture* texOneFuel;
	SDL_Texture* texNoFuel;
	SDL_Texture* texItemBattery;
	SDL_Texture* texExplosion;
	SDL_Texture* texDeadFuel;
	SDL_Texture* texDeadWater;
	SDL_Texture* texSpaceship;



	bool fullFuel = false;
	bool threeFuel = false;
	bool twoFuel = false;
	bool oneFuel = false;
	bool noFuel = false;

	int counter = 0;
	int deadCounter = 0;
	int explosionCounter = 0;
	Planet* earth;
	Planet* moon;

	bool tooFast = false;
	bool felip = false;
	bool explosion = false;

	bool spaceship = false;

	bool game = false;
	bool win = false;
	bool winMoon = false;
	bool dead = false;
	bool almostDead = false;
	bool battery1Take = false;
	bool battery2Take = false;
	bool battery3Take = false;
	bool battery4Take = false;

	bool battery1Taken = false;
	bool battery2Taken = false;
	bool battery3Taken = false;
	bool battery4Taken = false;

	bool springActive = false;
	bool outTrampoline = false;
	bool prova = false;
	int count = 0;
	bool water = false;
	bool inWater = false;

	bool firstJump = false;

	int counterAngle = 0;

	uint explosionFx;
	uint fuelUpFx;
	uint outOfFuelFx;
	uint jumpFx;
	uint splashFx;
	uint winFx;
};

#endif // __SCENE_H__