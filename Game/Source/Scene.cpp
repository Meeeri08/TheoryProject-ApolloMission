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
	img = app->tex->Load("Assets/Textures/test.png");
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


	if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		app->physicsEngine->rocket->AddMomentum(0.0f, -20.0f);


	if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		app->physicsEngine->rocket->AddMomentum(0.0f, 20.0f);
		
		
	if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		app->physicsEngine->rocket->AddMomentum(-20.0f, 0.0f);
		
		
	if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		app->physicsEngine->rocket->AddMomentum(20.0f, 0.0f);
	
		

	

	//LOG("position of the rocket x = %.2f  y = %.2f", rocket->pos.x, rocket->pos.y);
	

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	
	app->render->DrawCircle(app->physicsEngine->rocket->pos.x, app->physicsEngine->rocket->pos.y, app->physicsEngine->rocket->radius, 255, 0, 0);
	app->render->DrawCircle(earth->pos.x, earth->pos.y, earth->radius, 255, 0, 0);

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
