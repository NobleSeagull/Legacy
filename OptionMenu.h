#pragma once
#include "Drawable.h"

#include "Sound.h"

class OptionMenu
{
public:
	OptionMenu(SDL_Renderer *r, Sound *s);
	~OptionMenu();
	void Update(SDL_Renderer *r, EventListener *e, State &state);
	void Render(SDL_Renderer *r);

private:
	Drawable optMenu;
	int timer;
	Sound *m_sound;
};