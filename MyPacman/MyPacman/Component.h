#include "Message.h"

#pragma once
class Component
{
public:
	virtual ~Component() {};
	virtual void receive(Message message, GameObject &other, GameObject &object) = 0;
};

