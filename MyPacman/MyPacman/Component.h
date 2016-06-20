#include "Message.h"

#pragma once
class Component
{
public:
	virtual ~Component() {};
	virtual void receive(Message message, int objectId, GameObject &object) = 0;
};

