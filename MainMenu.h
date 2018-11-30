#pragma once
#include "Drawable.h"
#include "Sound.h"


class MainMenu
{
public:
	MainMenu(SDL_Renderer *r, Sound *s);
	~MainMenu();
	void Update(SDL_Renderer *r, EventListener *e, State &state, bool &gameRunning);
	void Render(SDL_Renderer *r);

private:
	Drawable mainMenu;
	int timer;
	Sound *m_sound;
};