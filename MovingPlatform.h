#pragma once
#include "SDL.h"
#include "Block.h"
#include "GameObject.h"
#include <vector>

enum Direction
{
	VERTICAL,
	HORIZONTAL
};

class MovingPlatform : public GameObject
{
public:
	MovingPlatform() {}
	MovingPlatform(int x, int y, SDL_Texture* t, b2World * w, Direction dir);
	~MovingPlatform() {}

	void Update(EventListener * eventListener);
	void Render(SDL_Renderer & r, SDL_RendererFlip* f);

private:
	bool moveRight;
	bool moveLeft;
	bool moveUp;
	bool moveDown;
	int startPosHor;
	int startPosVert;
};
