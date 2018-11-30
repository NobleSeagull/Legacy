#include "GlassShard.h"

GlassShard::GlassShard()
{
	
}

GlassShard::~GlassShard()
{

}


GlassShard::GlassShard(int x, int y,int width, int height, SDL_Texture * texture, b2World * w)
{
	m_box = Box(x, y, width, height, texture, w);
	m_box.PlayerAnimation(false);
}

void GlassShard::Update(EventListener * eventListener)
{
	
}

void GlassShard::Render(SDL_Renderer & r, SDL_RendererFlip* f)
{
	m_box.Render(r, f);
}