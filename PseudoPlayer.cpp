#include "PseudoPlayer.h"

PseudoPlayer::PseudoPlayer(int x, int y, SDL_Texture * texture, b2World *w, SDL_RendererFlip f)
{
	m_box = Box(x, y, 24, 24, texture, w);
	m_box.DeadSprite(true);
	m_box.PlayerAnimation(true);
	m_box.SetFlip(f);
	m_box.Body()->SetUserData((void*)objectIDEnum::PLAYER);
}

void PseudoPlayer::Render(SDL_Renderer & r, SDL_RendererFlip* f)
{
	m_box.Render(r, f);
}

void PseudoPlayer::Update(EventListener * eventListener)
{
	m_box.Update();
}
