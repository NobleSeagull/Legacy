#pragma once
#include "GameObject.h"

class GlassShard : public GameObject
{
public:
	GlassShard();
	~GlassShard();
	GlassShard(int x, int y,int width, int height, SDL_Texture * texture, b2World * w);
	void Update(EventListener * eventListener);
	void Render(SDL_Renderer & r, SDL_RendererFlip* f);
private:

};

