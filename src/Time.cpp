#include "Time.hpp"
#include <GLFW/glfw3.h>

bool  Time::_init = false;
double Time::_prevTime = 0.f;
double Time::_currTime = 0.f;
float Time::_dt = 0.f;

double Time::getTimeSinceAppStart()
{
	return glfwGetTime();
}

float Time::getDeltatime()
{	
	return _dt;
}

void Time::update()
{
	if (!_init)
	{
		_init = true;
		_prevTime = getTimeSinceAppStart();
	}

	_currTime = getTimeSinceAppStart();
	_dt = ((float)(_currTime - _prevTime));
    _prevTime = getTimeSinceAppStart();
}