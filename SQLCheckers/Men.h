#pragma once
#include <WMPEngine/SpriteBatch.h>
#include <glm/glm.hpp>
#include "BoardTile.h"

const int MENSIZE = 64;

class Men
{
public:
	Men();
	~Men();

	void draw(WMPEngine::SpriteBatch& spriteBatch);

	void MoveTo(glm::vec2 position);
	void SetOwner(int value) { owner = value; }
	int GetOwner() { return owner; }
	glm::vec2 GetPos() const { return position; }
	BoardTile* GetTile() { return currentTile; }
	void SetTile(BoardTile* tile) { currentTile = tile; }
	void SetAside();
	void SetKing() { isKing = true; }
	bool GetKing() { return isKing; }
	bool GetID() { return ID; }
	BoardTile* currentTile;
private:
	int owner;
	bool isKing;
	glm::vec2 position;
	WMPEngine::ColorRGBA8 color;
	int ID;
	
};

