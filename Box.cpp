#include "Box.h"
#include <iostream>


Box::Box()
{
}

Box::Box(int x, int y, int width, int height, SDL_Color color, b2World* World)
{
	m_rect.x = x;
	m_rect.y = y;
	m_rect.w = width;
	m_rect.h = height;

	m_color = color;
	m_RigidBody = false;

	m_bodyDef.type = b2_staticBody; //this will be a dynamic body
	m_bodyDef.position.Set(m_rect.x + m_rect.w / 2, m_rect.y + m_rect.h / 2); //set the starting position
	m_bodyDef.angle = 0; //set the starting angle
	m_body = World->CreateBody(&m_bodyDef);

	m_polygon.SetAsBox(m_rect.w / 2, m_rect.h / 2);

	m_Textured = false;

	m_polygonfixture.shape = &m_polygon;
	m_polygonfixture.density = 1;
	m_polygonfixture.restitution = 0.0;
	m_polygonfixture.friction = 0.5;
	m_body->CreateFixture(&m_polygonfixture);
	m_body->SetUserData((void*)objectIDEnum::NOTSET);
}

Box::Box(int x, int y, int width, int height, SDL_Texture * texture, b2World* World)
{
	m_rect.x = x;
	m_rect.y = y;
	m_rect.w = width;
	m_rect.h = height;

	m_Textured = true;
	m_texture = texture;

	m_RigidBody = true;

	m_center.x = m_rect.w * 0.5f;
	m_center.y = m_rect.h * 0.5f;

	m_bodyDef.type = b2_dynamicBody; //this will be a dynamic body
	m_bodyDef.position.Set(m_rect.x + m_rect.w/2, m_rect.y + m_rect.h/2); //set the starting position
	m_bodyDef.angle = 0; //set the starting angle
	m_body = World->CreateBody(&m_bodyDef);

	m_polygon.SetAsBox(m_rect.w/2, m_rect.h/2);
                  
	m_body->SetUserData((void*)objectIDEnum::NOTSET);

                  
	m_body->SetUserData((void*)objectIDEnum::NOTSET);

	m_polygonfixture.shape = &m_polygon;
	m_polygonfixture.density = 0.1;
	m_polygonfixture.restitution = 0.0;
	m_polygonfixture.friction = 0.0;
	m_body->CreateFixture(&m_polygonfixture);

	m_body->SetAngularVelocity(0);

	m_spriteRect.x = m_spriteRect.w * 6;;
	m_spriteRect.y = 0;
	m_spriteRect.w = width;
	m_spriteRect.h = height;
	m_panelTimer = 0;
	m_panel = 0;
	m_dead = false;
}

Box::Box(int x, int y, int width, int height, SDL_Texture * texture, b2World* World, bool kin)
{
	m_rect.x = x;
	m_rect.y = y;
	m_rect.w = width;
	m_rect.h = height;

	m_Textured = true;
	m_texture = texture;

	m_RigidBody = true;

	m_center.x = m_rect.w * 0.5f;
	m_center.y = m_rect.h * 0.5f;

	m_bodyDef.type = b2_kinematicBody; //this will be a kinematic body
	m_bodyDef.position.Set(m_rect.x + m_rect.w / 2, m_rect.y + m_rect.h / 2); //set the starting position
	m_bodyDef.angle = 0; //set the starting angle
	m_body = World->CreateBody(&m_bodyDef);

	m_polygon.SetAsBox(m_rect.w / 2, m_rect.h / 2);

	m_body->SetUserData((void*)objectIDEnum::NOTSET);

	m_polygonfixture.shape = &m_polygon;
	m_polygonfixture.density = 1;
	m_polygonfixture.restitution = 0.0;
	m_polygonfixture.friction = 0.0;
	m_body->CreateFixture(&m_polygonfixture);

	m_body->SetAngularVelocity(0);

	m_spriteRect.x = m_spriteRect.w * 6;;
	m_spriteRect.y = 0;
	m_spriteRect.w = width;
	m_spriteRect.h = height;
	m_panelTimer = 0;
	m_panel = 0;
	m_dead = false;
}

void Box::Update()
{
	if (m_animated && !m_dead)
	{
		if (m_body->GetLinearVelocity().x > 0.5)
		{
			Flip = SDL_FLIP_NONE;
		}
		else if (m_body->GetLinearVelocity().x < -0.5)
		{
			Flip = SDL_FLIP_HORIZONTAL;
		}

		if (state == "idle")
		{
			m_spriteRect.x = m_spriteRect.w * 6;
		}
		if (state == "walk")
		{
			m_spriteRect.x = m_spriteRect.w * (m_panel+6);
		}
		if (state == "jump")
		{
			m_spriteRect.x = m_spriteRect.w * (m_panel + 2);
		}
		if (state == "fall")
		{
			m_spriteRect.x = m_spriteRect.w * 1;
		}
		if (m_panelTimer <= 0)
		{
			if (m_panel < 3)
			{
				m_panel++;
			}
			else
			{
				m_panel = 0;
			}
			m_panelTimer = 4;
		}
		else
		{
			m_panelTimer--;
		}

	}
	else if (m_dead)
	{
		m_spriteRect.x = m_spriteRect.w * 0;
	}

	if (m_body->GetLinearVelocity().y <= 0.0001 && m_body->GetLinearVelocity().y >= -0.0001)
	{
		m_body->SetLinearVelocity(b2Vec2((m_body->GetLinearVelocity().x / 100) * 98, m_body->GetLinearVelocity().y));
	}
}

void Box::ApplyForce(float x, float y)
{
	b2Vec2 holder= b2Vec2(m_body->GetMass() * x, m_body->GetMass() * y);
	m_body->ApplyForce(holder, m_body->GetWorldCenter(), true);
}
void Box::ApplyVelocity(float x, float y)
{
	b2Vec2 holder = b2Vec2(m_body->GetLinearVelocity().x + x, m_body->GetLinearVelocity().y + y);
	m_body->SetLinearVelocity(holder);
}


void Box::Render(SDL_Renderer & r, SDL_RendererFlip* f)
{
	b2Vec2 pos = m_body->GetPosition();
	m_angle = m_body->GetAngle();

	m_angle = 180/3.14 * m_angle;                            
	m_rect.x = pos.x;
	m_rect.y = pos.y;

	SDL_Rect temp = m_rect;
	temp.x = m_rect.x - m_rect.w / 2;
	temp.y = m_rect.y - m_rect.h / 2;

	if (m_RigidBody)
	{
		if (m_animated)
		{
			SDL_RenderCopyEx(&r, m_texture, &m_spriteRect, &temp, m_angle, &m_center, Flip);
		}
		else if (m_dead)
		{
			SDL_RenderCopyEx(&r, m_texture, NULL, &temp, m_angle, &m_center, *f);
		}
		else
		{
			SDL_RenderCopyEx(&r, m_texture, NULL, &temp, m_angle, &m_center, *f);
		}
	}
	else
	{
		if (!m_Textured)
		{
			SDL_SetRenderDrawColor(&r, m_color.r, m_color.g, m_color.b, m_color.a);
			SDL_RenderFillRect(&r, &temp);
		}
	}
}

b2Body* Box::getBody()
{
	return m_body;
}
