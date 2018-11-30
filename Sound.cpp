#include "Sound.h"
#include <iostream>

Sound::Sound()
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	background = Mix_LoadMUS("Resources/background.wav");
	gameMusic = Mix_LoadMUS("Resources/gameMusic.wav");
	button = Mix_LoadWAV("Resources/button.wav");
	death = Mix_LoadWAV("Resources/death.wav");
	glass = Mix_LoadWAV("Resources/glass.wav");
	jump = Mix_LoadWAV("Resources/jump.wav");
	win = Mix_LoadWAV("Resources/win.wav");
	soundToggle = true;
	PlayMenuMusic();
}

Sound::~Sound() {}

void Sound::PlayGameMusic()
{
	if (soundToggle) {
		Mix_HaltMusic();
		Mix_PlayMusic(gameMusic, -1);
	}
}

void Sound::PlayMenuMusic()
{
	if (soundToggle) {
		Mix_HaltMusic();
		Mix_PlayMusic(background, -1);
	}
}

void Sound::PlayButton()
{
	if (soundToggle) {
		Mix_PlayChannel(-1, button, 0);
	}
}

void Sound::PlayDeath()
{
	if (soundToggle) {
		Mix_PlayChannel(-1, death, 0);
	}
}

void Sound::PlayGlass()
{
	if (soundToggle) {
		Mix_PlayChannel(-1, glass, 0);
	}
}

void Sound::PlayJump()
{
	if (soundToggle) {
		Mix_PlayChannel(-1, jump, 0);
	}
}

void Sound::PlayWin()
{
	if (soundToggle) {
		Mix_PlayChannel(-1, win, 0);
	}
}