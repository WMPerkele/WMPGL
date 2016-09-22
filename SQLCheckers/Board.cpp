#include "Board.h"
#include <iostream>

Board::Board()
{
}


Board::~Board()
{
	for (auto tile : tiles)
	{
		delete tile;
	}
	for (auto man : men)
	{
		delete man;
	}
}

void Board::init()
{
	bool black = true;
	for (int y = 1; y < 9; y++)
	{
		for (int x = 1; x < 9; x++)
		{
			black = !black;
			BoardTile* tile = new BoardTile();
			tile->Init(black, x, y);
			tiles.push_back(tile);
			
		}
		black = !black;
	}
	bool isPlayer1 = true;
	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i]->isBrown() == true && (i < 24 || i > 39))
		{
			Men* temp = new Men();
			temp->MoveTo(tiles[i]->GetPos());
			tiles[i]->SetVacant(temp);
			if (isPlayer1)
				temp->SetOwner(1);
			else
				temp->SetOwner(2);
			men.push_back(temp);
		}

		if (i > (tiles.size() / 2))
			isPlayer1 = false;
	}
}

void Board::draw(WMPEngine::SpriteBatch& _spriteBatch)
{
	for (auto tile : tiles)
	{
		tile->draw(_spriteBatch);
	}
	for (auto man : men)
	{
			man->draw(_spriteBatch);
	}
}

BoardTile* Board::hoveredTile(glm::vec2 position)
{
	for (auto tile : tiles)
	{
		if ((position.x > tile->GetPos().x && position.y > tile->GetPos().y)
			&& (position.x < tile->GetPos().x + TILESIZE && position.y < tile->GetPos().y + TILESIZE))
			return tile;
	}
	return nullptr;
}

Men* Board::hoveredMan(glm::vec2 position)
{
	for (auto man : men)
	{
		if ((position.x > man->GetPos().x && position.y > man->GetPos().y)
			&& (position.x < man->GetPos().x + TILESIZE && position.y < man->GetPos().y + TILESIZE))
			return man;
	}
	return nullptr;
}

bool Board::MoveIsLegal(Men* man, BoardTile* tile)
{
	if (man == nullptr || tile == nullptr || !tile->isBrown())
		return false;
	int modifier = 1;
	if (man->GetOwner() == 2)
		modifier = -1;

	if (man->GetKing())
	{
		if (tile->GETY() == man->GetTile()->GETY() - modifier)
		{
			if (tile->GETX() == man->GetTile()->GETX() - 1 || tile->GETX() == man->GetTile()->GETX() + 1)
				return true;
		}
	}
	if (tile->GETY() == man->GetTile()->GETY() + modifier)
	{
		{
			if (tile->GETX() == man->GetTile()->GETX() - 1 || tile->GETX() == man->GetTile()->GETX() + 1)
				return true;
		}
	}

	return false;
}

BoardTile* Board::MovePiece(Men* man, int x, int y)
{
	BoardTile* tile = GetTile(x, y);
	if (tile == nullptr)
		return nullptr;
	if (tile->GetVacant() != nullptr)
	{
		if (tile->GetVacant()->GetOwner() != man->GetOwner())
		{
			x = tile->GETX() - man->GetTile()->GETX();
			y = tile->GETY() - man->GetTile()->GETY();
			x = x * 2;
			y = y * 2;
			BoardTile* oldTile = tile;
			tile = GetTile(man->GetTile()->GETX() + x, man->GetTile()->GETY() + y);
			if (tile == nullptr || tile->GetVacant() != nullptr)
				return nullptr;
			oldTile->GetVacant()->SetAside();
			oldTile->SetVacant(nullptr);
			pieceWasAte = true;
		}
		else if (tile->GetVacant()->GetOwner() == man->GetOwner())
			return nullptr;
	}
	man->GetTile()->SetVacant(nullptr);
	man->MoveTo(tile->GetPos());
	tile->SetVacant(man);
	if (man->GetOwner() == 1)
	{
		if (man->GetTile()->GETY() == 8)
			man->SetKing();
	}
	else
	{
		if (man->GetTile()->GETY() == 1)
			man->SetKing();
	}
	return tile;
}

BoardTile* Board::GetTile(int x, int y)
{
	for (int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i]->GETX() == x && tiles[i]->GETY() == y)
			return tiles[i];
	}
	return nullptr;
}