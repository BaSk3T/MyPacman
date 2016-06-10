#pragma once
class Component
{
public:
	virtual ~Component() {};
	virtual void receive(int message, int objectId) = 0;
};

