#include "Portal.h"



Portal::Portal(int x, int y, LevelMessenger * l, std::vector<GameObject*>* o)
{
	m_messenger = l;
	m_x = x;
	m_y = y;
	m_objects = o;
}

void Portal::Update(EventListener * eventListener)
{
	SDL_Rect temp = { m_x, m_y, 48, 48 };
	for (int i = 0; i < m_objects->size(); i++)
	{
		if (typeid(*m_objects->at(i)) == typeid(Player))
		{
			if (SDL_HasIntersection(&m_objects->at(i)->m_box.Rectangle(), &temp))
			{
				m_messenger->message = "loadnext";
			}
		}
	}
}

void Portal::Render(SDL_Renderer & r, SDL_RendererFlip* f)
{
	SDL_Rect temp;
	temp.x = m_x;
	temp.y = m_y;
	temp.w = 48;
	temp.h = 48;

	SDL_SetRenderDrawColor(&r, 255, 123, 9, 155);
	SDL_RenderFillRect(&r, &temp);
}