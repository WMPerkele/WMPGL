#pragma once
#include "BoardTile.h"
#include "Men.h"
#include <vector>
#include <WMPEngine\SpriteBatch.h>
class Board
{
public:
	Board();
	~Board();

	void draw(WMPEngine::SpriteBatch& _spriteBatch);
	void init();

	BoardTile* hoveredTile(glm::vec2 position);
	Men* hoveredMan(glm::vec2 position);
	bool MoveIsLegal(Men* man, BoardTile* tile);
	BoardTile* MovePiece(Men* man, int x, int y);
	BoardTile* GetTile(int x, int y);
	bool pieceWasAte;
private:
	std::vector<BoardTile*> tiles;
	std::vector<Men*> men;

};

