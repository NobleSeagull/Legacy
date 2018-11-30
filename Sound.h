#pragma once
#include "SDL_mixer.h"

class Sound {
public:
	Sound();
	~Sound();
	void PlayMenuMusic();
	void PlayJump();
	void PlayDeath();
	void PlayButton();
	void PlayGlass();
	void PlayWin();
	void PlayGameMusic();
	bool soundToggle;

private:
	Mix_Music *background;
	Mix_Music *gameMusic;
	Mix_Chunk *jump;
	Mix_Chunk *death;
	Mix_Chunk *button;
	Mix_Chunk *glass;
	Mix_Chunk *win;
};