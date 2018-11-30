#include "stdafx.h"
#include "MovingPlatform.h"
#include <iostream>

MovingPlatform::MovingPlatform(int x, int y, SDL_Texture* t, b2World * w, Direction dir)
{
	m_box = Box(x, y, 48, 48, t, w, true);
	m_box.PlayerAnimation(false);
	m_box.getBody()->SetUserData((void*)objectIDEnum::PLATFORM);

	if (dir == Direction::VERTICAL)
	{
		startPosVert = m_box.GetBoxPosition().y;
		moveUp = true;
		moveDown = false;
	}

	if (dir == Direction::HORIZONTAL)
	{
		startPosHor = m_box.GetBoxPosition().x;
		moveRight = true;
		moveLeft = false;
	}
}

void MovingPlatform::Update(EventListener* eventListener)
{
	//Move Right and Left
	if (moveRight)
	{
		m_box.Body()->SetLinearVelocity(b2Vec2(5, 0));
	}
	if (m_box.GetBoxPosition().x > startPosHor + 96 && moveRight)
	{
		moveRight = false;
		moveLeft = true;
	}

	if (moveLeft)
	{
		m_box.Body()->SetLinearVelocity(b2Vec2(-5, 0));
	}
	if (m_box.GetBoxPosition().x < startPosHor && moveLeft)
	{
		moveLeft = false;
		moveRight = true;
	}

	//Move Up and Down
	if (moveUp)
	{
		m_box.Body()->SetLinearVelocity(b2Vec2(0, -5));
	}
	if (m_box.GetBoxPosition().y < startPosVert - 96 && moveUp)
	{
		//m_box.ApplyVelocity(0, 0);
		moveUp = false;
		moveDown = true;
		
	}

	if (moveDown)
	{
		m_box.Body()->SetLinearVelocity(b2Vec2(0, 5));
	}
	if (m_box.GetBoxPosition().y > startPosVert && moveDown)
	{
		//m_box.ApplyVelocity(0, 0);
		moveDown = false;
		moveUp = true;
	}
	
}

void MovingPlatform::Render(SDL_Renderer & r, SDL_RendererFlip* f)
{
	m_box.Render(r, f);
}