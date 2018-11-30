#include "OptionMenu.h"


OptionMenu::OptionMenu(SDL_Renderer *r, Sound *s)
{
	optMenu.AddText(100, 100, "Sound", 42, r);
	optMenu.AddText(100, 200, "Back", 42, r);
	m_sound = s;
}

OptionMenu::~OptionMenu() {}

void OptionMenu::Render(SDL_Renderer *r)
{
	optMenu.Render(r);
}


void OptionMenu::Update(SDL_Renderer *r, EventListener *e, State &state)
{
	timer++;
	if (e->UP == true && timer > 15)
	{
		optMenu.SwitchUp(r);
		timer = 0;
	}
	else if (e->DOWN == true && timer > 15)
	{
		optMenu.SwitchDown(r);
		timer = 0;
	}
	else if (e->RETURN == true && timer > 15)
	{
		if (optMenu.getSelected() == 0)
		{
			if (m_sound->soundToggle)
			{
				Mix_HaltMusic();
				m_sound->soundToggle = !m_sound->soundToggle;
			}
			else
			{
				m_sound->soundToggle = !m_sound->soundToggle;
				m_sound->PlayMenuMusic();
			}
		}
		else if (optMenu.getSelected() == 1)
		{
			state = State::mainM;
		}
		timer = 0;
	}
}