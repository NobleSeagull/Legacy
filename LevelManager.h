
#ifndef _LEVELMANAGER_H_
#define _LEVELMANAGER_H_
#include "LevelData.h"
#include <iostream>
#include <vector>
#include "LevelConstructor.h"
#include "GameObject.h"
#include "LevelMessenger.h"
#include "EventListener.h"
#include "State.h"
#include "Sound.h"

class LevelManager
{
public:
	LevelManager(std::vector<GameObject*>* objects, b2World *world, EventListener* e, SDL_Texture * t, SDL_Texture * tg, SDL_Texture * tp, Sound * s) { m_objects = objects; m_world = world; m_playerTexture = t; m_glassTexture = tg; m_platformTexture = tp;  m_messenger = new LevelMessenger(); m_event = e; m_sound = s; };
	~LevelManager() {};

	void LoadLevel(int x) { m_constructor.Construct(m_objects, m_messenger,*m_levels.at(x), m_world, m_playerTexture, m_glassTexture,m_platformTexture, m_sound); m_currentLevel = x; };
	void ResetLevel() { m_constructor.Construct(m_objects, m_messenger,*m_levels.at(m_currentLevel), m_world, m_playerTexture, m_glassTexture, m_platformTexture, m_sound); };

	void Update(State * s) 
	{
		if (m_messenger->message == "load")
		{
			m_messenger->message = "";
			m_currentLevel = m_messenger->level;
			if (m_currentLevel < m_levels.size())
			{
				LoadLevel(m_currentLevel);
			}
			else
			{
				*s = State::END;
				m_currentLevel = 0;
				LoadLevel(m_currentLevel);
			}
		}
		else if (m_messenger->message == "loadnext")
		{
			m_messenger->message = "";
			m_currentLevel++;
			if (m_currentLevel < m_levels.size())
			{
				LoadLevel(m_currentLevel);
			}
			else
			{
				*s = State::END;
				m_currentLevel = 0;
				LoadLevel(m_currentLevel);
			}
		}
		else if (m_messenger->message == "reset" || m_event->RESET == true)
		{
			m_messenger->message = "";
			ResetLevel();
		}
	}

	void AddLevel(LevelData* x) { m_levels.push_back(x); };

private:

	std::vector<LevelData*> m_levels;
	std::vector<GameObject*>* m_objects;
	b2World* m_world;
	SDL_Texture* m_playerTexture;
	SDL_Texture* m_glassTexture;
	SDL_Texture* m_platformTexture;
	LevelConstructor m_constructor;
	int m_currentLevel;
	LevelMessenger * m_messenger;
	EventListener * m_event;
	Sound * m_sound;
};
#endif