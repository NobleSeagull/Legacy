#ifndef _INPUTHANDLER_H_
#define _INPUTHANDLER_H_
#include "SDL.h"
#include "EventListener.h"
class InputHandler
{
public:
	InputHandler(SDL_Event * e, EventListener * ep) { m_e = e; m_eventlisten = ep; };
	~InputHandler();

	void InputCheck();
private:
	SDL_Event * m_e;
	EventListener * m_eventlisten;

};
#endif
