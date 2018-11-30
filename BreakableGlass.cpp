#include "BreakableGlass.h"

BreakableGlass::BreakableGlass()
{

}

BreakableGlass::~BreakableGlass()
{

}

BreakableGlass::BreakableGlass(int x, int y, SDL_Texture * texture, b2World * w, Sound *s)
{
	//201, 219, 220, 150
	glassColour = SDL_Color{ 201, 219, 220, 50 };
	m_box = Box(x, y, 48, 48, glassColour, w);
	isBroken = false;
	m_box.getBody()->SetUserData((void*)objectIDEnum::GLASSBOX);
	shardTexture = texture;
	//w->SetContactListener(this);
	pWorld = w;
	m_sound = s;
	SetupShards();
}

void BreakableGlass::Update(EventListener * eventListener)
{
	if (isBroken == false)
	{
		m_box.Body()->SetActive(true);
		for (b2Contact* contact = pWorld->GetContactList(); contact; contact = contact->GetNext())
		{
			//Checks if One of the Objects is glass
			int idObjA = (int)contact->GetFixtureA()->GetBody()->GetUserData();
			int idObjB = (int)contact->GetFixtureB()->GetBody()->GetUserData();
			b2Fixture* objGlass;
			b2Fixture* objOther;
			if (idObjA == objectIDEnum::GLASSBOX)
			{
				objGlass = contact->GetFixtureA();
				objOther = contact->GetFixtureB();
			}
			else if (idObjB == objectIDEnum::GLASSBOX)
			{
				objGlass = contact->GetFixtureB();
				objOther = contact->GetFixtureA();
			}
			//If both objects are not glass return
			else
			{
				return;
			}

			if (objGlass->GetBody() == m_box.Body())
			{
				if (objOther->GetBody()->GetLinearVelocity().y > 30)
				{
					//Check for collision between Player and Glass
					if ((int)objOther->GetBody()->GetUserData() == objectIDEnum::PLAYER)
					{
						BreakGlass(objOther->GetBody()->GetLinearVelocity(), b2Vec2(0, 0));
					}
				}
			}
		}

		for (int i = 0; i < shapeVector.size(); i++)
		{
			shapeVector[i]->m_box.getBody()->SetAwake(false);
			shapeVector.at(i)->m_box.getBody()->SetActive(false);
		}
	}
	else
	{
		m_box.Body()->SetActive(false);
		for (int i = 0; i < shapeVector.size(); i++)
		{
			shapeVector[i]->Update(eventListener);
			shapeVector[i]->m_box.getBody()->SetAwake(true);
			shapeVector.at(i)->m_box.getBody()->SetActive(true);
		}
	}
}

void BreakableGlass::Render(SDL_Renderer & r, SDL_RendererFlip* f)
{
	if (isBroken == false)
	{
		m_box.Render(r, f);
	}
	else
	{
		for (int i = 0; i < shapeVector.size(); i++)
		{
			shapeVector[i]->Render(r, f);
		}
	}

}

void BreakableGlass::BreakGlass(b2Vec2 playerVelocity, b2Vec2 collisionPoint)
{
	m_sound->PlayGlass();
	isBroken = true;
	for (int i = 0; i < shapeVector.size(); i++)
	{
		shapeVector[i]->m_box.getBody()->ApplyLinearImpulse(b2Vec2(0, 5 * playerVelocity.y), b2Vec2(collisionPoint.x, collisionPoint.y), true);
		shapeVector[i]->m_box.getBody()->SetAngularVelocity(playerVelocity.y);
	}
}


void BreakableGlass::SetupShards()
{
	shardWidth = (int)(m_box.Rectangle().w / 7.0f);
	shardHeight = (int)(m_box.Rectangle().h / 6.0f);

	for (int r = 0; r < 6; r++)
	{
		for (int c = 0; c < 7; c++)
		{
			shapeVector.push_back(new GlassShard(m_box.Rectangle().x + (shardWidth*c) , m_box.Rectangle().y + (shardHeight*r), shardWidth, shardHeight, shardTexture, m_box.getBody()->GetWorld()));
			shapeVector.at(shapeVector.size() - 1)->m_box.getBody()->SetActive(false);
			shapeVector.at(shapeVector.size() - 1)->m_box.getBody()->SetUserData((void*)objectIDEnum::GLASSSHARD);
		}
	}

}


void BreakableGlass::BeginContact(b2Contact *contact)
{

	
}

void BreakableGlass::EndContact(b2Contact *contact)
{

}

void BreakableGlass::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{

}

void BreakableGlass::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{

}