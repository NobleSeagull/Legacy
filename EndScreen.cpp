#include "stdafx.h"
#include "EndScreen.h"

EndScreen::EndScreen(SDL_Renderer* renderer)
{
	end.AddImage(400, 400, "Resources/logo.png", renderer);
	end.AddText(120, 50, "Congratulations", 50, renderer);
	end.AddText(190, 120, "Game Complete", 30, renderer);
	end.AddText(190, 250, "Press 'q' To Quit", 30, renderer);
	end.AddText(100, 300, "Press Enter to return to start", 30, renderer);
}

EndScreen::~EndScreen() {}

void EndScreen::Update(EventListener* e, State& s, bool& gameRunning)
{
	if (e->QUIT == true)
	{
		gameRunning = false;
	}

	if (e->RETURN == true)
	{
		s = State::SPLASH;
	}
}

void EndScreen::Render(SDL_Renderer* r)
{
	end.Render(r);
}