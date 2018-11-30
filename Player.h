#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "GameObject.h"
#include "PseudoPlayer.h"
#include <iostream>
#include "Sound.h"
#include <vector>

class Player :
	public GameObject
{
public:
	Player(int x, int y, SDL_Texture * texture, b2World *w, std::vector<GameObject*>* objects, Sound *s);
	~Player() {};

	void Update(EventListener * eventListener);
	void Render(SDL_Renderer & r, SDL_RendererFlip* f);

private:
	bool m_inAir;
	bool m_apexReached;
	bool m_dead;
	int m_maxApexHeight;
	std::vector<GameObject*>* m_Pobjects;
	b2World * m_world;
	SDL_Texture * m_texture;
	b2Vec2 m_respawnPoint;
	Sound *m_sound;
};
#endif

