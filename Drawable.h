#pragma once
#include <SDL.h>
#include "SDL_image.h"
#include <string>
#include <vector>
#include "SDL_ttf.h"
#include "State.h"
#include "EventListener.h"

class Drawable {
public:
	Drawable();
	~Drawable();
	void Render(SDL_Renderer * r);
	void AddText(int x, int y, const char * message, int size, SDL_Renderer * r); //Add a text object
	void AddImage(int x, int y, const char * filepath, SDL_Renderer * r); //Add an image object
	void SwitchUp(SDL_Renderer *r);
	void SwitchDown(SDL_Renderer *r);
	int getSelected();

private:
	SDL_Renderer * renderer;
	std::vector<SDL_Rect> rects; //Vector for rects for images
	std::vector<SDL_Rect> textRects; //Vector for rects for text
	SDL_Rect textureRect;
	SDL_Texture *t;
	SDL_Texture* text;
	SDL_Rect textRect;
	int text_height;
	int text_width;
	std::vector<SDL_Texture*> textures; //Vector for images
	std::vector<SDL_Texture*> texts; //Vector for text
	std::vector<const char*> messages;
	SDL_Surface* textSurface;
	TTF_Font* font;
	int selected;
	bool first;
	int timer;
};