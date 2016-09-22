#pragma once
#include <WMPEngine\SpriteBatch.h>
#include <WMPEngine\ResourceManager.h>
#include <glm\glm.hpp>


class Men;

	const int TILESIZE = 64;
enum TileType
{
	BrownTile,
	BlackTile
};

class BoardTile
{
public:
	BoardTile();
	~BoardTile();

	void draw(WMPEngine::SpriteBatch& _spriteBatch);

	void Init(bool isBlack, int X,  int Y);
	int GETX() const { return x; }
	int GETY() const { return y; }
	int GetID() const { return tileID; }
	glm::vec2 GetPos() const { return tilePos; }
	bool isBrown() { return tileType == BrownTile; }

	Men* GetVacant();
	void SetVacant(Men* man);
private:
	Men* vacant;
	int x, y;
	int tileID;
	glm::vec2 tilePos;
	WMPEngine::ColorRGBA8 tileColor;
	TileType tileType;
};

