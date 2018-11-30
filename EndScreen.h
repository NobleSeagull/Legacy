#pragma once
#include "SDL.h"
#include "Drawable.h"
#include "EventListener.h"
#include "State.h"

class EndScreen
{
public:
	EndScreen() {}
	EndScreen(SDL_Renderer* renderer);
	~EndScreen();

	void Update(EventListener* e, State& s, bool& gameRunning);
	void Render(SDL_Renderer* r);

private:
	Drawable end;
};
