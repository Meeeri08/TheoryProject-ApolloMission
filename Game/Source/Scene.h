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

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

private:
	SDL_Texture* background;
	SDL_Texture* texRocket;
	SDL_Texture* texWin;
	SDL_Texture* texIntro;
	SDL_Texture* texTrampoline;
	SDL_Texture* texFullFuel;
	SDL_Texture* texThreeFuel;
	SDL_Texture* texTwoFuel;
	SDL_Texture* texOneFuel;
	SDL_Texture* texNoFuel;
	SDL_Texture* texItemBattery;

	bool fullFuel;
	bool threeFuel;
	bool twoFuel;
	bool oneFuel;
	bool noFuel;

	int counter;

	Planet* earth;
	Planet* moon;

	bool game = false;
	bool win = false;
	bool winMoon = false;

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
	
};

#endif // __SCENE_H__