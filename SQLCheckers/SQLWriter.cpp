#include "SQLWriter.h"


SQLWriter::SQLWriter()
{

}

SQLWriter::~SQLWriter()
{

}

sqlite3* SQLWriter::init()
{
	sqlite3* retDB;
	int rc;
	rc = sqlite3_open(dbName, &retDB);
	if (rc)
	{
		std::cout << "Couldn't open database " << dbName << ":" << sqlite3_errmsg(retDB) << "\n";
		return nullptr;
	}
	else
	{
		std::cout << "Opened database " << dbName << "\n";
		return retDB;
	}
}

int SQLWriter::Callback(void *data, int argc, char **argv, char **azColName){
	int *pRows = (int*)data;
	(*pRows)++;
	if (*pRows<2) {
		for (int i = 0; i<argc; i++){
			std::cout << azColName[i] << "|";
		}
		std::cout << "\n";
	}
	for (int i = 0; i<argc; i++){
		std::cout << (argv[i] ? argv[i] : "NULL") << "|";
	}
	std::cout << "\n";
	return 0;
}

void SQLWriter::Query(std::string query)
{
	static int rows;
	int rc;
	char *zErrMsg = NULL;

	std::cout << query << std::endl;

	rc = sqlite3_exec(db, query.c_str(), Callback, (void*)&rows, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		std::cout << "BEGIN failed with SQL error: \"" << zErrMsg << "\"\n";
		sqlite3_free(zErrMsg);
		std::cout << "Closing database " << dbName << "\n";
		sqlite3_close(db);
	}

}

void SQLWriter::AddGame(int Player1ID, int Player2ID)
{
	static int gameID;
	gameID++;
	std::string query = "insert into Game(id, TurnsTaken, Player_id, Player2_id) values (";
	query += std::to_string(gameID) + ", " + std::to_string(0) + ", " + std::to_string(Player1ID) + ", " + std::to_string(Player2ID) + ");";

	Query(query);
}
void SQLWriter::AddPlayer(std::string name)
{
	static int playerID;
	playerID++;
	std::string query = "insert into Player(id, GamesPlayed, PlayerName) values (";
	query += std::to_string(playerID) + ", " + std::to_string(0) + ", \"" + name.c_str() + "\");";

	Query(query);
}
void SQLWriter::AddTurn(int GameID, int PlayerID)
{
	static int turnID;
	turnID++;
	std::string query = "insert into Turn(id, Game_id, Player_id) values (";
	query += std::to_string(turnID) + ", " + std::to_string(GameID) + ", " + std::to_string(PlayerID) + ");";

	Query(query);
}

void SQLWriter::AddMove(int XMov, int YMov, int TurnID, int PawnID)
{
	static int moveID;
	moveID++;
	std::string query = "insert into Move(id, XMovement, YMovement, Turn_id, PawnID) values (";
	query += std::to_string(moveID) + ", " + std::to_string(XMov) + ", " + std::to_string(YMov) + ", " + std::to_string(TurnID) + ", " + std::to_string(PawnID) + ");";

	Query(query);

}