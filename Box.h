#ifndef _BOX_H_
#define _BOX_H_

#include <iostream>
#include <Box2D\Box2D.h>
#include <SDL.h>
#include <SDL_image.h>

#include "ObjectID.h"

class Box
{
public:
	Box();
	Box(int x, int y, int width, int height, SDL_Color color, b2World* World);
	Box(int x, int y, int width, int height, SDL_Texture * texture, b2World* World);
	Box(int x, int y, int width, int height, SDL_Texture * texture, b2World* World, bool kin);
	~Box() {};

	void Update();
	void Render(SDL_Renderer & r, SDL_RendererFlip* f);

	void ApplyForce(float x, float y);
	void ApplyVelocity(float x, float y);

	SDL_Rect Rectangle() { return m_rect; };
	b2Body* getBody();

	b2Vec2 Center() { return b2Vec2(m_center.x, m_center.y); };
	b2Vec2 Velocity() { return m_body->GetLinearVelocity(); };
	b2Body* Body() { return m_body; };

	void SetBoxPosition(float x, float y) { m_body->SetTransform(b2Vec2(x, y), 0); };
	b2Vec2 GetBoxPosition() { return m_body->GetPosition(); }

	SDL_Texture * GetTexture() { return m_texture; };

	void PlayerAnimation(bool x) { m_animated = x; };
	void DeadSprite(bool x) { m_dead = x; };

	void SetFlip(SDL_RendererFlip x) { Flip = x; };
	SDL_RendererFlip GetFlip() { return Flip; }

	std::string state;

private:
	bool m_RigidBody;
	bool m_Textured;
	bool m_animated;
	bool m_dead;

	SDL_RendererFlip Flip;

	int m_panel;
	int m_panelTimer;
	SDL_Rect m_spriteRect;

	float m_angle;
	SDL_Rect m_rect;

	SDL_Color m_color;
	SDL_Texture * m_texture;

	//Box 2D stuff
	b2Body* m_body;
	b2BodyDef m_bodyDef;
	b2PolygonShape m_polygon;
	b2FixtureDef m_polygonfixture;
	//

	SDL_Point m_center;

};
#endif

