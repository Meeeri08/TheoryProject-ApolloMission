#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Body.h"
#include "PhysicsEngine.h"



#include "Defs.h"
#include "Log.h"


Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	background = app->tex->Load("Assets/Textures/background_space.png");
	texRocket = app->tex->Load("Assets/Textures/rocket.png");
	//app->audio->PlayMusic("Assets/Audio/Music/earth_scene.ogg");
	
	app->physicsEngine->rocket = app->physicsEngine->CreateRocket(Vec2(500,500), 5, Vec2(0,0), 20, 10, 50.0f);
	earth = app->physicsEngine->CreatePlanet(Vec2(600, 900), 20, 300);
	
	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{

	/*if(app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->render->camera.y -= 1;

	if(app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->render->camera.y += 1;

	if(app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->render->camera.x -= 1;

	if(app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->render->camera.x += 1;*/

	//Rocket movement
	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->physicsEngine->rocket->AddMomentum(0.0f, -2.8f);


	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->physicsEngine->rocket->AddMomentum(0.0f, 2.8f);
		
		
	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		//app->physicsEngine->rocket->AddMomentum(-2.8f, 0.0f);
		
		
	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		//app->physicsEngine->rocket->AddMomentum(2.8f, 0.0f);
	
	//Camera movement

	if (app->physicsEngine->rocket->pos.y < 220) app->render->camera.y = -(app->physicsEngine->rocket->pos.y - 220);
	

	//LOG("position of the rocket x = %.2f  y = %.2f", rocket->pos.x, rocket->pos.y);
	

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;
	app->render->DrawTexture(background, 0, -9000);

	//SDL_Rect rect = currentAnimation->GetCurrentFrame();
	app->render->DrawTexture(texRocket, app->physicsEngine->rocket->pos.x, app->physicsEngine->rocket->pos.y/*, &rect*/);
	

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");
	app->tex->UnLoad(texRocket);
	return true;
}
