#ifndef _EVENTLISTENER_H_
#define _EVENTLISTENER_H_
#include <iostream>
#include <list>

class EventListener
{
public:
	EventListener() {};
	~EventListener() {};

	bool LEFT = false;
	bool RIGHT = false;
	bool SPACE = false;
	bool RETURN = false;
	bool QUIT = false;
	bool UP = false;
	bool DOWN = false;
	bool RESET = false;
};
#endif