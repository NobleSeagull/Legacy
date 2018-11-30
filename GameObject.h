#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_
#include "Box.h"
#include "EventListener.h"

class GameObject
{
public:
	GameObject() {};
	~GameObject() {};

	virtual void Update(EventListener * eventListener) = 0;
	virtual void Render(SDL_Renderer & r, SDL_RendererFlip* f) = 0;

	SDL_Point Position()
	{
		return SDL_Point{ m_box.Rectangle().x, m_box.Rectangle().y };
	}
	Box m_box;
};
#endif

