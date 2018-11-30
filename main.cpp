#include "stdafx.h"

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <vector>

#include "Box2D\Box2D.h"
#include "SDL.h"
#include "SDL_image.h"

#include "SplashScreen.h"
#include "EndScreen.h"

#include "State.h"

#include "Block.h"
#include "JSONReader.h"

#include "LevelData.h"
#include "LevelConstructor.h"

#include "InputHandler.h"

#include "MainMenu.h"
#include "OptionMenu.h"

#include "PseudoPlayer.h"

#include "Sound.h"
#include "LevelManager.h"

using namespace std;

const int SCREEN_WIDTH = 576;
const int SCREEN_HEIGHT = 480;

SDL_Window* gameWindow;
SDL_Renderer* gameRenderer;
SDL_Event event;

Sound sound;

b2World* World;

b2Vec2 Gravity = b2Vec2(0, 9.81f);

bool gameRunning = true;
bool audio = true;

SplashScreen splashScreen;
EndScreen endScreen;

int main(int argc, char *args[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		exit(0);
	}

	EventListener * eventListener = new EventListener();
	JSONReader levelLoader = "DATA/Levels.json";

	World = new b2World(Gravity);
	World->SetGravity(Gravity);
	//Init
	gameWindow = SDL_CreateWindow("Legacy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawBlendMode(gameRenderer, SDL_BLENDMODE_BLEND);

	SDL_Surface * image = IMG_Load("Resources/Player.png");
	SDL_Texture * texture = SDL_CreateTextureFromSurface(gameRenderer, image);

	//Glass Texture
	SDL_Surface * imageGlass = IMG_Load("Resources/glass.png");
	SDL_Texture * textureGlass = SDL_CreateTextureFromSurface(gameRenderer, imageGlass);
	SDL_SetTextureBlendMode(textureGlass, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(textureGlass, 50);


	//Platform Texture
	SDL_Surface * imagePlatform = IMG_Load("Resources/platform.png");
	SDL_Texture * texturePlatform = SDL_CreateTextureFromSurface(gameRenderer, imagePlatform);
	//SDL_SetTextureBlendMode(texturePlatform, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(texturePlatform, 50);


	splashScreen = SplashScreen(gameRenderer);
	endScreen = EndScreen(gameRenderer);

	float timeStep = 0.05f;
	int velIter = 1.0;
	int posIter = 1.0;
	World->Step(timeStep, velIter, posIter);

	State state = State::SPLASH;


	InputHandler * input = new InputHandler(&event, eventListener);

	std::vector<GameObject*>* GameObjects = new std::vector<GameObject*>;

	//Level Managment
	LevelManager* levelManager = new LevelManager(GameObjects, World, eventListener, texture, textureGlass, texturePlatform, &sound);
	levelLoader.loadLevel(0);
	levelManager->AddLevel(new LevelData(levelLoader.Level()));
	levelLoader.loadLevel(1);
	levelManager->AddLevel(new LevelData(levelLoader.Level()));
	levelManager->LoadLevel(0);
	//


	MainMenu mainMenu(gameRenderer, &sound);
	OptionMenu optMenu(gameRenderer, &sound);

	while (gameRunning)
	{
		//Update code
		input->InputCheck();
		levelManager->Update(&state);
		if (state == State::SPLASH)
		{
			splashScreen.Update(eventListener, state);
		}

		if (state == State::END)
		{
			endScreen.Update(eventListener, state, gameRunning);
		}
		if (state == State::playGame)
		{
			World->Step(timeStep, velIter, posIter);
			for (int i = 0; i < GameObjects->size(); i++)
			{
				GameObjects->at(i)->Update(eventListener);
			}
		}
		else if (state == State::mainM)
		{
			mainMenu.Update(gameRenderer, eventListener, state, gameRunning);
		}
		else if (state == State::optM)
		{
			optMenu.Update(gameRenderer, eventListener, state);
		}


		//end update code
		SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 0);
		SDL_RenderClear(gameRenderer);

		//draw code
		SDL_RendererFlip Flip = SDL_FLIP_NONE;
		if (state == State::SPLASH)
		{
			splashScreen.Render(gameRenderer);
		}
		if (state == State::END)
		{
			endScreen.Render(gameRenderer);
		}
		if (state == State::playGame)
		{
			for (int i = 0; i < GameObjects->size(); i++)
			{
				GameObjects->at(i)->Render(*gameRenderer, &Flip);
			}
		}
		else if (state == State::mainM)
		{
			mainMenu.Render(gameRenderer);
		}
		else if (state == State::optM)
		{
			optMenu.Render(gameRenderer);
		}

		//end draw code
		SDL_RenderPresent(gameRenderer);
	}
	

	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(gameRenderer);

	SDL_Quit();

	return 0;
}
