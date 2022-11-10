#pragma once
#include "Tile.h"
#include <vector>
#include "MineCounter.h"
#include "GameInfo.h"
using namespace std;


class Board
{
private:
	short columns = 0;
	short rows = 0;
	short tileNumber = 0;
	short mineCount = 0;
	short revealedCount = 0;
	bool isGameOver = false;
	vector<Tile> listOfTiles;
	map<string, Tile> mapOfUITiles;
	MineCounter currentCounter;
	map<string, sf::Texture>* ptrToMapOfTextures;
	int random(int min, int max);
public:
	GameInfo* origConfig;
	GameInfo* test1;
	GameInfo* test2;
	GameInfo* test3;
	Board(short rows, short columns, short tileNumber, map<string, sf::Texture>& mapOfTextures, short mineCount, GameInfo& test1, GameInfo& test2, GameInfo& test3, GameInfo& origConfig);
	Tile& GetTile(short row, short column);
	Tile* FindClickedUITile(float x, float y);
	Tile& GetUITile(string UITileName);
	vector<Tile>& GetListOfTiles();
	map<string, Tile>& GetMapOfUITiles();
	MineCounter& GetMineCounter();
	void IncRevealedCount();
	void EndGame(map<string, sf::Texture>& mapOfTextures, string result);
	void NewGame();
	void TestGame(GameInfo* optionalGameInfoPtr);
	bool GetGameOver();
};