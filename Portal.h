#pragma once
#include "GameObject.h"
#ifndef _PORTAL_H_
#define _PORTAL_H_
#include "GameObject.h"
#include <iostream>
#include <vector>
#include "LevelMessenger.h"
#include "Player.h"

class Portal : public GameObject
{
public:
	Portal(int x, int y, LevelMessenger * l, std::vector<GameObject*>* o);
	~Portal() {};

	void Update(EventListener * eventListener);
	void Render(SDL_Renderer & r, SDL_RendererFlip* f);

private:

	int m_x, m_y;
	int m_nextLevel;
	LevelMessenger * m_messenger;
	std::vector<GameObject*>* m_objects;
};
#endif