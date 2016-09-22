#include "Men.h"
#include <WMPEngine\ResourceManager.h>
#include <iostream>


Men::Men()
{
	static int id;
	ID = id++;
}


Men::~Men()
{
}

void Men::draw(WMPEngine::SpriteBatch& spriteBatch)
{
	static int textureID = WMPEngine::ResourceManager::getTexture("Textures/circle.png").id;
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(position.x, position.y, MENSIZE, MENSIZE);
	if (owner == 1)
		color = WMPEngine::ColorRGBA8{ 255, 0, 0, 255 };
	else
		color = WMPEngine::ColorRGBA8{ 105, 105, 105, 255 };
	spriteBatch.draw(destRect, uvRect, textureID, 0.0f, color);
}

void Men::MoveTo(glm::vec2 position)
{
	this->position = position;
}

void Men::SetAside()
{
	this->MoveTo(glm::vec2(-64, -64));
	SetTile(nullptr);
}