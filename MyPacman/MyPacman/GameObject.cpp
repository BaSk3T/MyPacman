#include "GameObject.h"

GameObject::GameObject(double x, double y, InputComponent *input, PhysicsComponent *physics, GraphicsComponent *graphics)
	: x(x),
	y(y),
	input(input),
	physics(physics),
	graphics(graphics)
{
}

GameObject::~GameObject()
{
	delete this->input;
	delete this->physics;
	delete this->graphics;
}

void GameObject::update(World &world, SystemGraphics &graphics, SystemInput &input)
{
	this->input->update(*this, input);
	this->physics->update(*this, world);
	this->graphics->update(*this, graphics);
}

void GameObject::send(int message, int objectId)
{
	this->input->receive(message, objectId);
	this->physics->receive(message, objectId);
	this->graphics->receive(message, objectId);
}
