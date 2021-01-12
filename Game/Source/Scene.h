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

	Planet* earth;
	Planet* moon;
};

#endif // __SCENE_H__