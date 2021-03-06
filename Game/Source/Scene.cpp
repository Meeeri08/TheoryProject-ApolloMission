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
	background = app->tex->Load("Assets/Textures/background_space_prova.png");
	texRocket = app->tex->Load("Assets/Textures/rocket.png");
	texRocketUp = app->tex->Load("Assets/Textures/rocketUp.png");
	texWin = app->tex->Load("Assets/Textures/winText.png");
	texLose = app->tex->Load("Assets/Textures/loseText.png");
	texIntro = app->tex->Load("Assets/Textures/introText.png");
	texTrampoline = app->tex->Load("Assets/Textures/trampoline.png");
	texFullFuel = app->tex->Load("Assets/Textures/fullfuel.png");
	texThreeFuel = app->tex->Load("Assets/Textures/threefuel.png");
	texTwoFuel = app->tex->Load("Assets/Textures/twofuel.png");
	texOneFuel = app->tex->Load("Assets/Textures/onefuel.png");
	texNoFuel = app->tex->Load("Assets/Textures/nofuel.png");
	texItemBattery = app->tex->Load("Assets/Textures/itemBattery.png");
	texExplosion = app->tex->Load("Assets/Textures/explode.png");
	texDeadFuel = app->tex->Load("Assets/Textures/deadFuel.png");
	texDeadWater = app->tex->Load("Assets/Textures/splashOut.png");
	texSpaceship = app->tex->Load("Assets/Textures/spaceship.png");

	app->audio->PlayMusic("Assets/Audio/Music/outer_space.ogg");
	
	explosionFx = app->audio->LoadFx("Assets/Audio/Fx/explosion.wav");
	fuelUpFx = app->audio->LoadFx("Assets/Audio/Fx/fuelUp.wav");
	outOfFuelFx = app->audio->LoadFx("Assets/Audio/Fx/outOfFuel.wav");
	jumpFx = app->audio->LoadFx("Assets/Audio/Fx/Jump.wav");
	splashFx = app->audio->LoadFx("Assets/Audio/Fx/splash.wav");
	winFx = app->audio->LoadFx("Assets/Audio/Fx/winTone.wav");

	app->physicsEngine->rocket = app->physicsEngine->CreateRocket(Vec2(622, 480), 5, Vec2(0,0), 20, 10, 50.0f, 0.0f);

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
	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		game = true;
	}
	count++;

	//Bouyancy
	if ((app->physicsEngine->rocket->pos.x <= 384 || app->physicsEngine->rocket->pos.x >= 895) && app->physicsEngine->rocket->pos.y > 480&&count>=100&&!water)
	{
		app->physicsEngine->rocket->velocity.y = app->physicsEngine->rocket->velocity.y - 40;
		count = 0;
		inWater = true;
		app->audio->PlayFx(splashFx);
	}
	else if (app->physicsEngine->rocket->pos.y <= 480 && inWater)
	{
		app->physicsEngine->rocket->velocity.y = 0;
		water = true;
	}


	if (game == true && !dead && !almostDead)
	{
		if (felip == false)
		{
			app->physicsEngine->rocket->velocity.y = 0;
			app->physicsEngine->rocket->pos.y = 480;
			felip = true;
		}

		//terra mort per toofast
		if (app->physicsEngine->rocket->pos.y > 480 && app->physicsEngine->rocket->velocity.y > 800 && app->physicsEngine->rocket->pos.x >= 384 && app->physicsEngine->rocket->pos.x <= 895)
		{
			tooFast = true;
			win = false;
			deadCounter++;
			app->audio->PlayFx(explosionFx);
		}
		//terra mort per angle malament
		if (app->physicsEngine->rocket->pos.y > 480 && app->physicsEngine->rocket->pos.x >= 384 && app->physicsEngine->rocket->pos.x <= 895 && (app->physicsEngine->rocket->angle > 35 || app->physicsEngine->rocket->angle < -35))
		{
			tooFast = true;

			deadCounter++;
			app->audio->PlayFx(explosionFx);
		}

		//lluna mort per toofast
		if (app->physicsEngine->rocket->pos.y < -10450 && app->physicsEngine->rocket->velocity.y < -800 && app->physicsEngine->rocket->pos.x >= 384 && app->physicsEngine->rocket->pos.x <= 895)
		{
			tooFast = true;

			deadCounter++;
			app->audio->PlayFx(explosionFx);
		}
		//lluna mort per angle malament
		if (app->physicsEngine->rocket->pos.y < -10450 && app->physicsEngine->rocket->pos.x >= 384 && app->physicsEngine->rocket->pos.x <= 895 && (app->physicsEngine->rocket->angle < 145 && app->physicsEngine->rocket->angle > -145))
		{
			tooFast = true;

			deadCounter++;
			app->audio->PlayFx(explosionFx);
		}
	

		//angle correcte a la terra
		if (app->physicsEngine->rocket->pos.y >= 480 && app->physicsEngine->rocket->pos.x >= 384 && app->physicsEngine->rocket->pos.x <= 895 && app->physicsEngine->rocket->angle < 35 && app->physicsEngine->rocket->angle > -35 && app->physicsEngine->rocket->angle !=0)
		{
			if (counterAngle > 50) {
				if (app->physicsEngine->rocket->angle > 1)
				{
					app->physicsEngine->rocket->angle--;
				}
				else if (app->physicsEngine->rocket->angle < -1)
				{
					app->physicsEngine->rocket->angle++;
				}
				else
				{
					app->physicsEngine->rocket->angle = 0;
				}
				counterAngle = 0;
			}
			counterAngle++;
		}

		//angle correcte a la lluna
		if (app->physicsEngine->rocket->pos.y <= -10450 && app->physicsEngine->rocket->pos.x >= 384 && app->physicsEngine->rocket->pos.x <= 895 && (app->physicsEngine->rocket->angle < -145 || app->physicsEngine->rocket->angle > 145) && app->physicsEngine->rocket->angle != 0)
		{
			if (counterAngle > 50) {
				if (app->physicsEngine->rocket->angle < 179 && app->physicsEngine->rocket->angle > 145)
				{
					app->physicsEngine->rocket->angle++;
				}
				else if (app->physicsEngine->rocket->angle > -178 && app->physicsEngine->rocket->angle < -145)
				{
					app->physicsEngine->rocket->angle--;
				}
				else
				{
					app->physicsEngine->rocket->angle = 180;
				}
				counterAngle = 0;
			}
			counterAngle++;
		}


		//limits moon
		if (app->physicsEngine->rocket->pos.y < -10450 && app->physicsEngine->rocket->pos.x >= 384 && app->physicsEngine->rocket->pos.x <= 895)
		{
			app->physicsEngine->rocket->pos.y = -10450;
			app->physicsEngine->rocket->velocity.y = 0;
			app->physicsEngine->rocket->velocity.x = 0;
		}
		else if (app->physicsEngine->rocket->pos.y < -10450 && (app->physicsEngine->rocket->pos.x < 384 || app->physicsEngine->rocket->pos.x > 895))
		{
			tooFast = true;
			app->audio->PlayFx(explosionFx);

		}

		//limits earth
		if (app->physicsEngine->rocket->pos.y > 480 && !tooFast && app->physicsEngine->rocket->pos.x >= 384 && app->physicsEngine->rocket->pos.x <= 895)
		{
			app->physicsEngine->rocket->pos.y = 480;
			app->physicsEngine->rocket->velocity.y = 0;
			app->physicsEngine->rocket->velocity.x = 0;
		}

		
		//x limits
		if (app->physicsEngine->rocket->pos.x > 1244)
		{
			app->physicsEngine->rocket->pos.x = 1244;
			app->physicsEngine->rocket->velocity.x = 0;
		}
		if (app->physicsEngine->rocket->pos.x < 0)
		{
			app->physicsEngine->rocket->pos.x = 0;
			app->physicsEngine->rocket->velocity.x = 0;
		}

		///Fuel
		if (counter <= 25000)
		{
			fullFuel = true;
			threeFuel = false;
			twoFuel = false;
			oneFuel = false;
			noFuel = false;
		}
		if (counter > 25000 && counter <= 50000) {
			fullFuel = false;
			threeFuel = true;
			twoFuel = false;
			oneFuel = false;
			noFuel = false;
		}
		if (counter > 50000 && counter <= 75000) {
			fullFuel = false;
			threeFuel = false;
			twoFuel = true;
			oneFuel = false;
			noFuel = false;
		}
		if (counter > 75000 && counter <= 100000) {
			fullFuel = false;
			threeFuel = false;
			twoFuel = false;
			oneFuel = true;
			noFuel = false;
		}
		if (counter > 100000 && counter < 125000) {
			fullFuel = false;
			threeFuel = false;
			twoFuel = false;
			oneFuel = false;
			noFuel = true;
			app->audio->PlayFx(outOfFuelFx);
		}

		if (battery1Take && !battery1Taken)
		{
			counter -= 25000;
			battery1Taken = true;
			app->audio->PlayFx(fuelUpFx);
		}

		if ( battery2Take && !battery2Taken)
		{
			counter -= 25000;
			battery2Taken = true;
			app->audio->PlayFx(fuelUpFx);
		}
		if (battery3Take && !battery3Taken)
		{
			counter -= 25000;
			battery3Taken = true;
			app->audio->PlayFx(fuelUpFx);
		}
		if (battery4Take && !battery4Taken)
		{
			counter -= 25000;
			battery4Taken = true;
			app->audio->PlayFx(fuelUpFx);
		}
		if (app->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
		{
			dead = true;
		}

		if (noFuel||tooFast||spaceship) 
		{
			deadCounter++;
		}
		if (deadCounter >= 15000)
		{
			dead = true;
		}
		/*if(app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
			app->render->camera.y -= 1;

		if(app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
			app->render->camera.y += 1;

		if(app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
			app->render->camera.x -= 1;

		if(app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
			app->render->camera.x += 1;*/

			//Rocket movement
		if (!win)
		{
			if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && !noFuel && !inWater)
			{
				app->physicsEngine->rocket->AddMomentumAngle(1.1f, -1.1f, app->physicsEngine->rocket->angle);
				counter++;
				
			}

		}

		if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && !noFuel && !inWater)
		{
			app->physicsEngine->rocket->angle -= 0.02f;
			if (app->physicsEngine->rocket->angle < -180)
			{
				app->physicsEngine->rocket->angle = 180;
			}

		}
		if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && !noFuel && !inWater)
		{
			app->physicsEngine->rocket->angle += 0.02f;
			if (app->physicsEngine->rocket->angle > 180)
			{
				app->physicsEngine->rocket->angle = -180;
			}
		}

		//Change limit velocity
		if (app->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
		{
			if (app->physicsEngine->rocket->limitVelocityDown == 1000.0f)
			{
				app->physicsEngine->rocket->limitVelocityDown = 100000.0f;
				app->physicsEngine->rocket->limitVelocityUp = -100000.0f;
			}
			else
			{
				app->physicsEngine->rocket->limitVelocityDown = 1000.0f;
				app->physicsEngine->rocket->limitVelocityUp = -1000.0f;
			}
		}



		///batterys
		if (app->physicsEngine->rocket->pos.y  < -3410 && app->physicsEngine->rocket->pos.y > -3510)
		{
			if (app->physicsEngine->rocket->pos.x < 350 && app->physicsEngine->rocket->pos.x > 290)

			battery1Take = true;
		}
		if (app->physicsEngine->rocket->pos.y < -4910 && app->physicsEngine->rocket->pos.y > -5010)
		{
			if (app->physicsEngine->rocket->pos.x < 530 && app->physicsEngine->rocket->pos.x > 490)

				battery2Take = true;
		}
		if (app->physicsEngine->rocket->pos.y < -6410 && app->physicsEngine->rocket->pos.y > -6510)
		{
			if (app->physicsEngine->rocket->pos.x < 300 && app->physicsEngine->rocket->pos.x > 240)

				battery3Take = true;
		}
		if (app->physicsEngine->rocket->pos.y < -8410 && app->physicsEngine->rocket->pos.y > -8510)
		{
			if (app->physicsEngine->rocket->pos.x < 750 && app->physicsEngine->rocket->pos.x > 690)

				battery4Take = true;
		}


		///Spaceship
		if (app->physicsEngine->rocket->pos.y < -5310 && app->physicsEngine->rocket->pos.y > -5520)
		{
			if (app->physicsEngine->rocket->pos.x < 650 && app->physicsEngine->rocket->pos.x > 530)
			{
				spaceship = true;
				app->audio->PlayFx(explosionFx);
			}
		}
		if (app->physicsEngine->rocket->pos.y < -6300 && app->physicsEngine->rocket->pos.y > -6520)
		{
			if (app->physicsEngine->rocket->pos.x < 850 && app->physicsEngine->rocket->pos.x > 730)
			{
				spaceship = true;
				app->audio->PlayFx(explosionFx);
			}
	
		}



		//Camera movement
		if (app->physicsEngine->rocket->pos.y < 300 && !noFuel)
		{
			app->render->camera.y = -(app->physicsEngine->rocket->pos.y - 300);

		}
		if (app->physicsEngine->rocket->pos.y > 480 && (app->physicsEngine->rocket->pos.x <= 384 || app->physicsEngine->rocket->pos.x >= 895) && !noFuel)
		{
			app->render->camera.y = -(app->physicsEngine->rocket->pos.y - 480);
		}

	}

	if (dead || win)
	{
		HalfCleanUp();
		if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		{
			CleanUp();
			Restart();
		}
	}



	//SPRING
	if (app->physicsEngine->rocket->pos.y <= 434) springActive = true;


	if (!firstJump && app->physicsEngine->rocket->pos.y <= 494 && app->physicsEngine->rocket->pos.y >= 434 && app->physicsEngine->rocket->pos.x < 882 && app->physicsEngine->rocket->pos.x > 761 && springActive && !outTrampoline)
	{
		app->physicsEngine->rocket->velocity.y = -(app->physicsEngine->rocket->velocity.y / 1.01);
		firstJump = true;
	}

	if (firstJump && app->physicsEngine->rocket->pos.y <= 494 && app->physicsEngine->rocket->pos.y >= 434 && app->physicsEngine->rocket->pos.x < 882 && app->physicsEngine->rocket->pos.x > 761 && springActive && !outTrampoline)
	{
		if (prova && app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		{
			prova = false;
		}

		if (!prova) {
			float res = app->physicsEngine->rocket->velocity.y;
			app->physicsEngine->rocket->velocity.y = -(app->physicsEngine->rocket->velocity.y / 1.01);
			app->audio->PlayFx(jumpFx);
			if (res < 100 && res>-100)
			{
				prova = true;
			}
		}
		else {
			app->physicsEngine->rocket->velocity.y = -(app->physicsEngine->rocket->velocity.y);
		}
		
		outTrampoline = true;

	}

	if (outTrampoline && app->physicsEngine->rocket->pos.y < 454) outTrampoline = false;


	if (app->physicsEngine->rocket->pos.y > 454) springActive = false;


	return true;
}
// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;


	
	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	if (!game)  app->render->DrawTexture(texIntro, 0, -0);
	if (game)
	{
		app->render->DrawTexture(background, 0, -10780);
		app->render->DrawTexture(texTrampoline, 770, 480);

		app->render->DrawTexture(texSpaceship,550 , -5500);
		app->render->DrawTexture(texSpaceship, 750, -6500);

		if (!win) 
		{

			
			if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && !noFuel && !inWater)
			{
				app->render->DrawTexture(texRocketUp, app->physicsEngine->rocket->pos.x, app->physicsEngine->rocket->pos.y, 0, 1.0, app->physicsEngine->rocket->angle);
			}
			else {
				app->render->DrawTexture(texRocket, app->physicsEngine->rocket->pos.x, app->physicsEngine->rocket->pos.y, 0, 1.0, app->physicsEngine->rocket->angle);
			}

			if (fullFuel) app->render->DrawTexture(texFullFuel, -(app->render->camera.x-1100), -(app->render->camera.y-550));
			if (threeFuel) app->render->DrawTexture(texThreeFuel, -(app->render->camera.x - 1100), -(app->render->camera.y - 550));
			if (twoFuel) app->render->DrawTexture(texTwoFuel, -(app->render->camera.x - 1100), -(app->render->camera.y - 550));
			if (oneFuel) app->render->DrawTexture(texOneFuel, -(app->render->camera.x - 1100), -(app->render->camera.y - 550));
			if (noFuel) app->render->DrawTexture(texNoFuel, -(app->render->camera.x - 1100), -(app->render->camera.y - 550));

			if (!battery1Take)
			{
				app->render->DrawTexture(texItemBattery, 300, -3500);
			}
			if (!battery2Take)
			{
				app->render->DrawTexture(texItemBattery, 500, -5000);
			}
			if (!battery3Take)
			{
				app->render->DrawTexture(texItemBattery, 250, -6500);
			}
			if (!battery4Take)
			{
				app->render->DrawTexture(texItemBattery, 700, -8500);
			}

		}

		if (app->physicsEngine->rocket->pos.y <= -10449)
		{
			winMoon = true;
		}
		if (winMoon && app->physicsEngine->rocket->pos.y >= 480 && !tooFast)
		{
			counterWin++;
			if (counterWin >= 15000) 
			{
				app->render->DrawTexture(texWin, 0, 0);
				win = true;
			}
			app->audio->PlayFx(winFx);

		}
		if (dead && win || dead && !win)
		{
			app->physicsEngine->rocket->pos.y = 600;
			app->physicsEngine->rocket->pos.x = 622;
			app->render->camera.y = -600;
			app->tex->UnLoad(texNoFuel);

			app->render->DrawTexture(texLose, 0, app->physicsEngine->rocket->pos.y);
		}

		if (water)
		{
			app->tex->UnLoad(texRocket);
			app->tex->UnLoad(texRocketUp);

			app->render->DrawTexture(texDeadWater, app->physicsEngine->rocket->pos.x, app->physicsEngine->rocket->pos.y+20);
			app->physicsEngine->rocket->velocity.x = 0;

		}
		if (water && count >= 5000)
		{
			dead = true;
		}

		if (noFuel) 
		{
			app->physicsEngine->rocket->velocity.x = 0;
			app->physicsEngine->rocket->velocity.y = 0;
			app->tex->UnLoad(texRocket);
			app->tex->UnLoad(texRocketUp);


			app->render->DrawTexture(texDeadFuel, -(app->render->camera.x - 600), -(app->render->camera.y - 250));

		}
		if (spaceship)
		{
			app->physicsEngine->rocket->velocity.x = 0;
			app->physicsEngine->rocket->velocity.y = 0;
			app->tex->UnLoad(texRocket);
			app->tex->UnLoad(texRocketUp);
			app->render->DrawTexture(texExplosion, app->physicsEngine->rocket->pos.x, app->physicsEngine->rocket->pos.y);
		}

		if (tooFast)
		{
			app->physicsEngine->rocket->velocity.x = 0;
			app->physicsEngine->rocket->velocity.y = 0;
			app->tex->UnLoad(texRocket);
			app->tex->UnLoad(texRocketUp);
			app->render->DrawTexture(texExplosion, app->physicsEngine->rocket->pos.x, app->physicsEngine->rocket->pos.y);
		}

	}
	return ret;
}

bool Scene::Restart()
{
	Start();

	felip = false;
	tooFast = false;
	fullFuel = false;
	threeFuel = false;
	twoFuel = false;
	oneFuel = false;
	noFuel = false;
	water = false;
	inWater = false;
	spaceship = false;
	firstJump = false;


	count = 0;
	counterAngle = 0;
	explosionCounter = 0;
	counter = 0;
	deadCounter = 0;
	counterWin = 0;

	app->render->camera.y = 0;
	app->physicsEngine->rocket->velocity.y = 0;
	app->physicsEngine->rocket->pos.x = 622;
	app->physicsEngine->rocket->pos.y = 461;
	app->physicsEngine->rocket-> angle = 0;

	game = false;
	win = false;
	winMoon = false;
	dead = false;
	explosion = false;
	almostDead = false;
	battery1Take = false;
	battery2Take = false;
	battery3Take = false;
	battery4Take = false;

	battery1Taken = false;
	battery2Taken = false;
	battery3Taken = false;
	battery4Taken = false;

	springActive = false;
	outTrampoline = false;
	prova = false;

	return true;

}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");
	
	app->tex->UnLoad(background);
	app->tex->UnLoad(texRocket);
	app->tex->UnLoad(texRocketUp);
	app->tex->UnLoad(texWin);
	app->tex->UnLoad(texLose);
	app->tex->UnLoad(texIntro);
	app->tex->UnLoad(texTrampoline);
	app->tex->UnLoad(texFullFuel);
	app->tex->UnLoad(texThreeFuel);
	app->tex->UnLoad(texTwoFuel);
	app->tex->UnLoad(texOneFuel);
	app->tex->UnLoad(texNoFuel);
	app->tex->UnLoad(texItemBattery);
	app->tex->UnLoad(texExplosion);
	app->tex->UnLoad(texDeadWater);
	app->tex->UnLoad(texDeadFuel);
	app->tex->UnLoad(texSpaceship);

	return true;
}



bool Scene::HalfCleanUp()
{
	LOG("Freeing scene");

	app->tex->UnLoad(texRocket);
	app->tex->UnLoad(texRocketUp);
	app->tex->UnLoad(texItemBattery);
	app->tex->UnLoad(texExplosion);
	app->tex->UnLoad(texDeadWater);
	app->tex->UnLoad(texDeadFuel);
	return true;
}
