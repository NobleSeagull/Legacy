#pragma once
#include "GameObject.h"
#include "GlassShard.h"
#include <vector>
#include "Sound.h"

class BreakableGlass : public GameObject , public b2ContactListener
{
public:
	BreakableGlass();
	BreakableGlass(int x, int y, SDL_Texture * texture, b2World * w, Sound *s);
	void Update(EventListener * eventListener);
	void Render(SDL_Renderer & r, SDL_RendererFlip* f);
	void BreakGlass(b2Vec2 playerVelocity, b2Vec2 collisionPoint);
	void SetupShards();
	void BeginContact(b2Contact *contact);
	void EndContact(b2Contact *contact);
	void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);
	void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);
	~BreakableGlass();
	bool isBroken;

private:
	SDL_Color glassColour;

	std::vector<GlassShard*> shapeVector;
	SDL_Texture* shardTexture;
	int shardWidth;
	int shardHeight;
	b2World* pWorld;
	Sound *m_sound;
	
};

