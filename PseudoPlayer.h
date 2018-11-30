#ifndef _PSEUDOPLAYER_H_
#define _PSEUDOPLAYER_H_
#include "GameObject.h"

class PseudoPlayer :
	public GameObject
{
public:
	PseudoPlayer(int x, int y, SDL_Texture * texture, b2World *w, SDL_RendererFlip f);
	~PseudoPlayer() {};

	void Update(EventListener * eventListener);
	void Render(SDL_Renderer & r, SDL_RendererFlip* f);
};
#endif

