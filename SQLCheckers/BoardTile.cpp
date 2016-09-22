#include "Men.h"
#include "BoardTile.h"


BoardTile::BoardTile()
{
	static int ID;
	tileID = ID;
	vacant = nullptr;
	ID++;
	
	static glm::vec2 positionGiver;
	tilePos = positionGiver;

	positionGiver.x += TILESIZE;

	if (positionGiver.x > TILESIZE * 7)
	{
		positionGiver.x = 0;
		positionGiver.y += TILESIZE;
	}
}


BoardTile::~BoardTile()
{

}

void BoardTile::Init(bool isBlack, int X, int Y)
{
	if (isBlack)
	{
		tileType = BlackTile;
		tileColor = WMPEngine::ColorRGBA8{ 0, 0, 0, 255 };
	}
	else
	{
		tileType = BrownTile;
		tileColor = WMPEngine::ColorRGBA8{ 122, 82, 48, 255 };
	}
	x = X;
	y = Y;
}

void BoardTile::draw(WMPEngine::SpriteBatch& spriteBatch)
{
	static int textureID = WMPEngine::ResourceManager::getTexture("Textures/Tile.png").id;
	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(tilePos.x, tilePos.y, TILESIZE, TILESIZE);
	
	spriteBatch.draw(destRect, uvRect, textureID, 0.0f, tileColor);
}

Men* BoardTile::GetVacant()
{
	return vacant;
}

void BoardTile::SetVacant(Men* man) 
{ 
	vacant = man; 
	if (man != nullptr)
		man->SetTile(this);
}