#include "MainMenu.h"


MainMenu::MainMenu(SDL_Renderer *r, Sound *s)
{
	mainMenu.AddText(100, 100, "Play", 42, r);
	mainMenu.AddText(100, 200, "Options", 42, r);
	mainMenu.AddText(100, 300, "Exit", 42, r);
	m_sound = s;
}

MainMenu::~MainMenu() {}

void MainMenu::Render(SDL_Renderer *r)
{
	mainMenu.Render(r);
}

void MainMenu::Update(SDL_Renderer *r, EventListener *e, State &state, bool &gameRunning)
{
	timer++;
	if (e->UP == true && timer > 15)
	{
		mainMenu.SwitchUp(r);
		timer = 0;
	}
	else if (e->DOWN == true && timer > 15)
	{
		mainMenu.SwitchDown(r);
		timer = 0;
	}
	else if (e->RETURN == true && timer > 15)
	{
		if (mainMenu.getSelected() == 0)
		{
			state = State::playGame;
			m_sound->PlayGameMusic();
		}
		else if (mainMenu.getSelected() == 1)
		{
			state = State::optM;
		}
		else if (mainMenu.getSelected() == 2)
		{
			gameRunning = false;
		}
		timer = 0;

	}
}