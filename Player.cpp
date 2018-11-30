#include "Player.h"


Player::Player(int x, int y, SDL_Texture * texture, b2World *w, std::vector<GameObject*>* objects, Sound *s)
{
	m_box = Box(x, y, 24, 24, texture, w);
	m_dead = false;
	m_box.Body()->SetFixedRotation(true);
	m_box.PlayerAnimation(true);
	m_box.Body()->SetUserData((void*)objectIDEnum::PLAYER);
	m_texture = texture;
	m_Pobjects = objects;
	m_world = w;
	m_respawnPoint.x = x;
	m_respawnPoint.y = y;
	m_sound = s;
}

void Player::Render(SDL_Renderer & r, SDL_RendererFlip* f)
{
	m_box.Render(r, f);
}

void Player::Update(EventListener * eventListener)
{
	m_box.Update();
	//Event Listening
	if (eventListener->LEFT == true && !m_dead)
	{
		m_box.ApplyForce(-20, 0);
		std::cout << "LEFT" << std::endl;
	}
	if (eventListener->RIGHT == true && !m_dead)
	{
		m_box.ApplyForce(20, 0);
		std::cout << "RIGHT" << std::endl;
	}
	if (eventListener->SPACE == true && !m_inAir && !m_dead)
	{
		m_box.ApplyForce(0, -400);
		std::cout << "SPACE" << std::endl;
		m_apexReached = false;
		m_sound->PlayJump();
	}
	//
	if (m_box.Velocity().y > -0.05 && m_box.Velocity().y < 0.05 && m_apexReached)
	{
		m_inAir = false;
		if (m_box.Velocity().x < 0.5 && m_box.Velocity().x > -0.5)
		{
			m_box.state = "idle";
		}
		else
		{
			m_box.state = "walk";
		}
	}
	else if(m_box.Velocity().y > -1 && m_box.Velocity().y < 1 && !m_apexReached)
	{
		m_apexReached = true;
		m_maxApexHeight = m_box.Rectangle().y;
	}
	else
	{
		m_inAir = true;
	}

	if (m_inAir && !m_apexReached)
	{
		m_box.state = "jump";
	}
	else if (m_inAir && m_apexReached)
	{
		m_box.state = "fall";
	}

	for (b2Contact* contact = m_box.Body()->GetWorld()->GetContactList(); contact; contact = contact->GetNext())
	{
		//Checks if One of the Objects is glass
		int idObjA = (int)contact->GetFixtureA()->GetBody()->GetUserData();
		int idObjB = (int)contact->GetFixtureB()->GetBody()->GetUserData();
		b2Fixture* objPlayer;
		b2Fixture* objOther;
		if (idObjA == objectIDEnum::PLAYER)
		{
			objPlayer = contact->GetFixtureA();
			objOther = contact->GetFixtureB();
		}
		else if (idObjB == objectIDEnum::PLAYER)
		{
			objPlayer = contact->GetFixtureB();
			objOther = contact->GetFixtureA();
		}
		//If both objects are not glass return
		else
		{
			return;
		}

		if (objPlayer->GetBody() == m_box.Body())
		{
			if ((int)objOther->GetBody()->GetUserData() == objectIDEnum::PLATFORM)
			{
				m_apexReached = true;
				m_maxApexHeight = m_box.Rectangle().y;
				m_inAir = false;
				if (m_box.Velocity().x < 0.5 && m_box.Velocity().x > -0.5)
				{
					m_box.state = "idle";
				}
				else
				{
					m_box.state = "walk";
				}
			}
		}
	}

	if (m_box.Rectangle().y - m_maxApexHeight > 48 * 4)
	{
		m_dead = true;
	}

	if (m_dead == true && m_inAir == false)
	{
		m_box.DeadSprite(true);
	}

	if (m_box.Rectangle().y - m_maxApexHeight > 48 * 3 && m_inAir == false)
	{
		m_sound->PlayDeath();
		m_Pobjects->push_back(new PseudoPlayer(m_box.getBody()->GetPosition().x, m_box.getBody()->GetPosition().y, m_texture, m_world, m_box.GetFlip()));
		m_box.getBody()->SetTransform(m_respawnPoint, 0);
	}
	if (m_inAir == false)
	{
		m_maxApexHeight = m_box.Rectangle().y;
	}
}
