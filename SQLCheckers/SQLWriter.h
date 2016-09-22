#include <iostream>
#include <string>
#include "sqlite3.h"

class SQLWriter
{
public:
	SQLWriter();
	~SQLWriter();
	sqlite3* init();
	void AddGame(int Player1ID, int Player2ID);
	void AddPlayer(std::string name);
	void AddTurn(int GameID, int PlayerID);
	void AddMove(int XMov, int YMov, int TurnID, int PawnID);

private:
	const char *dbName = "Checkers.sqlite";
	sqlite3* db;
	static int Callback(void *data, int argc, char **argv, char **azColName);
	void Query(std::string query);
};