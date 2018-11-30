
#ifndef _LEVELCONSTRUCTOR_H_
#define _LEVELCONSTRUCTOR_H_


#include <iostream>
#include <vector>
#include "Block.h"
#include "Player.h"
#include "LevelData.h"
#include "BreakableGlass.h"
#include "MovingPlatform.h"
#include "LevelMessenger.h"
#include "Portal.h"

class LevelConstructor
{
public:

	LevelConstructor() {};

	void Construct(std::vector<GameObject*>* objects, LevelMessenger * l, LevelData data, b2World *World, SDL_Texture * t, SDL_Texture * tg, SDL_Texture * tp, Sound *s)
	{
		for (int i = 0; i < objects->size(); i++)
		{
			if (typeid(*objects->at(i)) != typeid(Portal))
			{
				World->DestroyBody(objects->at(i)->m_box.Body());
			}
		}
		objects->clear();
		for (int i = 0; i < data.elements.size(); i++)
		{
			for (int j = 0; j < data.elements.at(i).elements.size(); j++)
			{
				if (data.elements.at(j).elements.at(i) == 1)
				{
					objects->push_back(new Block(i * 48, j * 48, SDL_Color{ 255, 255, 255, 255 }, World));
				}
				else if (data.elements.at(j).elements.at(i) == 2)
				{
					objects->push_back(new Player(i * 48, j * 48, t, World, objects, s));
				}
				else if (data.elements.at(j).elements.at(i) == 4)
				{
					objects->push_back(new MovingPlatform(i * 48, j * 48, tp, World, Direction::VERTICAL)); //Up and Down Platform
				}
				else if (data.elements.at(j).elements.at(i) == 5)
				{
					objects->push_back(new MovingPlatform(i * 48, j * 48, tp, World, Direction::HORIZONTAL)); //Left and Right Platform
				}
				else if (data.elements.at(j).elements.at(i) == 3)
				{
					objects->push_back(new BreakableGlass(i * 48, j * 48, tg, World, s));
				}
				else if (data.elements.at(j).elements.at(i) == 9)
				{
					objects->push_back(new Portal(i * 48, j * 48, l, objects));
				}
			}
		}
	}
};
#endif
