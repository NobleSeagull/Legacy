#include "stdafx.h"
#include "SplashScreen.h"

SplashScreen::SplashScreen(SDL_Renderer* renderer)
{
	splash.AddImage(400, 400, "Resources/logo.png", renderer);
	splash.AddText(200, 50, "Legacy", 70, renderer);
	splash.AddText(70, 160, "A Game By Josh Quinn, Jason Hannon, Marc Gee & Matthew Watson", 15, renderer);
	splash.AddText(120, 190, "Real World Modelling 17-18, Project 2 November 17", 15, renderer);
	splash.AddText(140, 220, "Supervisors: Martin Harrigan & Daire O'Broin", 15, renderer);
	splash.AddText(160, 350, "Press Space To Start", 30, renderer);
}

SplashScreen::~SplashScreen() {}

void SplashScreen::Update(EventListener* e, State& s)
{
	if (e->SPACE == true)
	{
		s = State::mainM;
	}
}

void SplashScreen::Render(SDL_Renderer * r)
{
	splash.Render(r);
}