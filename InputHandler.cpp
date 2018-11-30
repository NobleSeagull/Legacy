#include "InputHandler.h"

InputHandler::~InputHandler()
{
}


void InputHandler::InputCheck()
{
	while (SDL_PollEvent(m_e) != 0)
	{
		switch (m_e->type)
		{
		case SDL_KEYDOWN:
		{
			switch (m_e->key.keysym.sym)
			{
			case SDLK_SPACE:
				m_eventlisten->SPACE = true;
				break;
			case SDLK_a:
				m_eventlisten->LEFT = true;
				break;
			case SDLK_d:
				m_eventlisten->RIGHT = true;
				break;
			case SDLK_LEFT:
				m_eventlisten->LEFT = true;
				break;
			case SDLK_RIGHT:
				m_eventlisten->RIGHT = true;
				break;
			case SDLK_RETURN:
				m_eventlisten->RETURN = true;
				break;
			case SDLK_q:
				m_eventlisten->QUIT = true;
				break;
			case SDLK_UP:
				m_eventlisten->UP = true;
				break;
			case SDLK_DOWN:
				m_eventlisten->DOWN = true;
				break;
			case SDLK_r:
				m_eventlisten->RESET = true;
				break;
			default:
				break;
			}
			break;
		}
		case SDL_KEYUP:
		{
			switch (m_e->key.keysym.sym)
			{
			case SDLK_SPACE:
				m_eventlisten->SPACE = false;
				break;
			case SDLK_a:
				m_eventlisten->LEFT = false;
				break;
			case SDLK_d:
				m_eventlisten->RIGHT = false;
				break;
			case SDLK_LEFT:
				m_eventlisten->LEFT = false;
				break;
			case SDLK_RIGHT:
				m_eventlisten->RIGHT = false;
				break;
			case SDLK_RETURN:
				m_eventlisten->RETURN = false;
				break;
			case SDLK_q:
				m_eventlisten->QUIT = true;
				break;
			case SDLK_UP:
				m_eventlisten->UP = false;
				break;
			case SDLK_DOWN:
				m_eventlisten->DOWN = false;
				break;
			case SDLK_r:
				m_eventlisten->RESET = false;
				break;
			default:
				break;
			}
			break;
		}
		}
	}
}