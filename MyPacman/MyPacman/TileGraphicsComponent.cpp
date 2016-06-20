#include "TileGraphicsComponent.h"

TileGraphicsComponent::TileGraphicsComponent(Rectangle clip) : clip(clip)
{
}

TileGraphicsComponent::~TileGraphicsComponent()
{
}

void TileGraphicsComponent::update(GameObject &object, SystemGraphics &graphics)
{
	graphics.draw("tile", (int)object.x, (int)object.y, this->clip);
}

void TileGraphicsComponent::receive(Message message, int objectId, GameObject &object)
{

}