#include "GameObject.h"

GameObject::GameObject(int objectId, double x, double y, InputComponent *input, PhysicsComponent *physics, GraphicsComponent *graphics)
	: objectId(objectId),
	x(x),
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

void GameObject::send(Message message, GameObject &other)
{
	this->input->receive(message, other, *this);
	this->physics->receive(message, other, *this);
	this->graphics->receive(message, other, *this);
}
