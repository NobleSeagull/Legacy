#include "Block.h"



Block::Block(int x, int y, SDL_Color color, b2World * w)
{
	m_box = Box(x, y, 48, 48, color, w);
	m_box.getBody()->SetUserData((void*)objectIDEnum::BLOCK);
}

void Block::Render(SDL_Renderer & r, SDL_RendererFlip* f)
{
	m_box.Render(r, f);
}