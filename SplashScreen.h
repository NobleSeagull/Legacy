#pragma once
#include "SDL.h"
#include "Drawable.h"
#include "EventListener.h"
#include "State.h"

class SplashScreen
{
public:
	SplashScreen() {}
	SplashScreen(SDL_Renderer* renderer);
	~SplashScreen();

	void Update(EventListener* e, State& s);
	void Render(SDL_Renderer * r);

private:
	Drawable splash;
};
