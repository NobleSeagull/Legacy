#ifndef _BLOCK_H_
#define _BLOCK_H_
#include "GameObject.h"
class Block : public GameObject
{
public:
	Block(int x, int y, SDL_Color color, b2World *w);
	~Block() {};

	void Update(EventListener * eventListener) {};
	void Render(SDL_Renderer & r, SDL_RendererFlip* f);
};
#endif