#include "Board.h"
#include <iostream>
#include <random>
#include <ctime>


using namespace std;
std::mt19937 random_mt;

Board::Board(short rows, short columns, short tileNumber, map<string, sf::Texture>& mapOfTextures, short mineCount, GameInfo& test1, GameInfo& test2, GameInfo& test3, GameInfo& origConfig) {
	this->origConfig = &origConfig;
	this->test1 = &test1;
	this->test2 = &test2;
	this->test3 = &test3;
	time_t timer;
	time(&timer);
	this->ptrToMapOfTextures = &mapOfTextures;
	this->rows = rows;
	this->columns = columns;
	this->tileNumber = tileNumber;
	this->mineCount = mineCount;
	random_mt.seed(timer);
	//Create the tiles that can contain mines
	for (short i = 0; i < tileNumber; i++) {
		short row = i / columns;
		short column = i % columns;
		Tile newTile(mapOfTextures["tile_hidden"], row, column, mapOfTextures);
		listOfTiles.push_back(newTile);
	}

	//Load the mines into the tiles that can contain mines
	short numMinesToGive = mineCount;

	for (short i = 0; i < mineCount;) {
		int randTileIndex = random(0, tileNumber - 1);
		Tile& currentTile = listOfTiles.at(randTileIndex);
		if (currentTile.GetHasMine() == false) {
			currentTile.AddMine();
			i++;
		}
	}
	//Assigned the neibors to each tile if the neibor exists
	for (short i = 0; i < tileNumber; i++) {
		short row = i / columns;
		short column = i % columns;
		Tile& currentTile = listOfTiles.at(i);
		//Cardinal Direction Pointers
		Tile* NTile = nullptr;
		try {
			NTile = &(this->GetTile(row - 1, column));
		}
		catch (std::out_of_range e) {

		}

		Tile* STile = nullptr;
		try {
			STile = &(this->GetTile(row + 1, column));
		}
		catch (std::out_of_range e) {

		}

		Tile* ETile = nullptr;
		try {
			ETile = &(this->GetTile(row , column + 1));
		}
		catch (std::out_of_range e) {

		}

		Tile* WTile = nullptr;
		try {
			WTile = &(this->GetTile(row , column - 1));
		}
		catch (std::out_of_range e) {

		}

		//Ordinal Direction Pointers
		Tile* NETile = nullptr;
		try {
			NETile = &(this->GetTile(row - 1, column + 1));
		}
		catch (std::out_of_range e) {

		}

		Tile* SETile = nullptr;
		try {
			SETile = &(this->GetTile(row + 1, column + 1));
		}
		catch (std::out_of_range e) {

		}

		Tile* SWTile = nullptr;
		try {
			SWTile = &(this->GetTile(row + 1, column - 1));
		}
		catch (std::out_of_range e) {

		}

		Tile* NWTile = nullptr;
		try {
			NWTile = &(this->GetTile(row - 1, column - 1));
		}
		catch (std::out_of_range e) {

		}

		currentTile.AddNeighbor("N", NTile);
		currentTile.AddNeighbor("S", STile);
		currentTile.AddNeighbor("E", ETile);
		currentTile.AddNeighbor("W", WTile);
		currentTile.AddNeighbor("NE", NETile);
		currentTile.AddNeighbor("SE", SETile);
		currentTile.AddNeighbor("SW", SWTile);
		currentTile.AddNeighbor("NW", NWTile);
		switch (currentTile.GetNumNeighborsWithMines()) {
		case 1:
			currentTile.LoadNumTexture(mapOfTextures["number_1"]);
			break;
		case 2:
			currentTile.LoadNumTexture(mapOfTextures["number_2"]);
			break;
		case 3:
			currentTile.LoadNumTexture(mapOfTextures["number_3"]);
			break;
		case 4:
			currentTile.LoadNumTexture(mapOfTextures["number_4"]);
			break;
		case 5:
			currentTile.LoadNumTexture(mapOfTextures["number_5"]);
			break;
		case 6:
			currentTile.LoadNumTexture(mapOfTextures["number_6"]);
			break;
		case 7:
			currentTile.LoadNumTexture(mapOfTextures["number_7"]);
			break;
		case 8:
			currentTile.LoadNumTexture(mapOfTextures["number_8"]);
			break;
		default:
			break;
		}

	}

	/*while (numMinesToGive > (short) 0) {
		for (size_t i = 0; i < listOfTiles.size(); i++) {
			short randNum = random(1, 2);
			cout << "Random num: " << randNum << endl;
			if (randNum == 1) {
				Tile& currentTile = listOfTiles.at(i);
				
				if (currentTile.GetHasMine() == false) {
					cout << "Giving a mine" << endl;
					currentTile.AddMine();
					numMinesToGive--;
					cout << "Num mines remaining to give: " << numMinesToGive << endl;
				}
				else {
					cout << "This tile has a mine: " << i << " Bool Value: " << currentTile.GetHasMine() << endl;
					cout << "Num mines remaining to give: " << numMinesToGive << endl;
				}
			}
			else {

			}
		}
	}*/
	short centerColumn = (columns - 1) / 2;
	Tile newSmileyFace(mapOfTextures["face_happy"], rows - 2, centerColumn, mapOfTextures);
	Tile newDebug(mapOfTextures["debug"], rows - 2, centerColumn + 2, mapOfTextures);
	Tile newTest1(mapOfTextures["test_1"], rows - 2, centerColumn + 4, mapOfTextures);
	Tile newTest2(mapOfTextures["test_2"], rows - 2, centerColumn + 6, mapOfTextures);
	Tile newTest3(mapOfTextures["test_3"], rows - 2, centerColumn + 8, mapOfTextures);
	mapOfUITiles["faceUI"] = newSmileyFace;
	mapOfUITiles["debugUI"] = newDebug;
	mapOfUITiles["test1UI"] = newTest1;
	mapOfUITiles["test2UI"] = newTest2;
	mapOfUITiles["test3UI"] = newTest3;

	MineCounter newCounter(mapOfTextures["digits"], rows - 2, 2, mineCount);
	currentCounter = newCounter;
}

Tile& Board::GetTile(short row, short column) {
	if (row < 0 || row > rows - 1 || column < 0 || column > columns - 1) {
		out_of_range newOutOfRangeException("Invalid row or column");
		throw newOutOfRangeException;
	}
	int indexOfTile = columns * row + column;
	return listOfTiles.at(indexOfTile);
	
}

Tile& Board::GetUITile(string UITileName) {
	return mapOfUITiles[UITileName];
}

vector<Tile>& Board::GetListOfTiles() {
	return listOfTiles;
}

map<string, Tile>& Board::GetMapOfUITiles() {
	return mapOfUITiles;
}

MineCounter& Board::GetMineCounter() {
	return currentCounter;
}

int Board::random(int min, int max) {
	uniform_int_distribution<int> dist(min, max);
	return dist(random_mt);
}

void Board::EndGame(map<string, sf::Texture>& mapOfTextures, string result) {
	isGameOver = true;
	if (result == "defeat") {
		for (size_t i = 0; i < listOfTiles.size(); i++) {
			Tile& currentTile = listOfTiles.at(i);
			if (currentTile.GetHasMine() == true) {
				currentTile.LoadTexture(mapOfTextures["tile_revealed"]);
				
			}
			else if (currentTile.GetHasFlag() == true) {
				currentCounter.Increment();
			}
		}
		Tile& smileyTile = GetUITile("faceUI");
		smileyTile.LoadTexture(mapOfTextures["face_lose"]);
	}
	else {

		Tile& smileyTile = GetUITile("faceUI");
		smileyTile.LoadTexture(mapOfTextures["face_win"]);
		for (size_t i = 0; i < listOfTiles.size(); i++) {
			Tile& currentTile = listOfTiles.at(i);
			if (currentTile.GetHasMine() == true) {
				currentTile.SetDebug(false);

				if (currentTile.GetHasFlag() == false) {
					currentTile.ToggleHasFlag(true);
					currentCounter.Decrement();
				}
			}
		}
	}
}

void Board::NewGame() {
	mineCount = origConfig->mineCount;
	revealedCount = 0;
	isGameOver = false;
	Tile& smileyTile = GetUITile("faceUI");
	smileyTile.LoadTexture((*ptrToMapOfTextures)["face_happy"]);
	listOfTiles.clear();
	currentCounter.UpdateCounter(mineCount);
	time_t timer;
	time(&timer);

	random_mt.seed(timer);
	//Create the tiles that can contain mines
	for (short i = 0; i < tileNumber; i++) {
		short row = i / columns;
		short column = i % columns;
		Tile newTile((*ptrToMapOfTextures)["tile_hidden"], row, column, (*ptrToMapOfTextures));
		listOfTiles.push_back(newTile);
	}

	//Load the mines into the tiles that can contain mines
	short numMinesToGive = 0;
	numMinesToGive = this->mineCount;

	for (short i = 0; i < numMinesToGive;) {
		int randTileIndex = random(0, tileNumber - 1);
		Tile& currentTile = listOfTiles.at(randTileIndex);
		if (currentTile.GetHasMine() == false) {
			currentTile.AddMine();
			i++;
		}
	}
	//Assigned the neibors to each tile if the neibor exists
	for (short i = 0; i < tileNumber; i++) {
		short row = i / columns;
		short column = i % columns;
		Tile& currentTile = listOfTiles.at(i);
		//Cardinal Direction Pointers
		Tile* NTile = nullptr;
		try {
			NTile = &(this->GetTile(row - 1, column));
		}
		catch (std::out_of_range e) {

		}

		Tile* STile = nullptr;
		try {
			STile = &(this->GetTile(row + 1, column));
		}
		catch (std::out_of_range e) {

		}

		Tile* ETile = nullptr;
		try {
			ETile = &(this->GetTile(row, column + 1));
		}
		catch (std::out_of_range e) {

		}

		Tile* WTile = nullptr;
		try {
			WTile = &(this->GetTile(row, column - 1));
		}
		catch (std::out_of_range e) {

		}

		//Ordinal Direction Pointers
		Tile* NETile = nullptr;
		try {
			NETile = &(this->GetTile(row - 1, column + 1));
		}
		catch (std::out_of_range e) {

		}

		Tile* SETile = nullptr;
		try {
			SETile = &(this->GetTile(row + 1, column + 1));
		}
		catch (std::out_of_range e) {

		}

		Tile* SWTile = nullptr;
		try {
			SWTile = &(this->GetTile(row + 1, column - 1));
		}
		catch (std::out_of_range e) {

		}

		Tile* NWTile = nullptr;
		try {
			NWTile = &(this->GetTile(row - 1, column - 1));
		}
		catch (std::out_of_range e) {

		}

		currentTile.AddNeighbor("N", NTile);
		currentTile.AddNeighbor("S", STile);
		currentTile.AddNeighbor("E", ETile);
		currentTile.AddNeighbor("W", WTile);
		currentTile.AddNeighbor("NE", NETile);
		currentTile.AddNeighbor("SE", SETile);
		currentTile.AddNeighbor("SW", SWTile);
		currentTile.AddNeighbor("NW", NWTile);
		switch (currentTile.GetNumNeighborsWithMines()) {
		case 1:
			currentTile.LoadNumTexture((*ptrToMapOfTextures)["number_1"]);
			break;
		case 2:
			currentTile.LoadNumTexture((*ptrToMapOfTextures)["number_2"]);
			break;
		case 3:
			currentTile.LoadNumTexture((*ptrToMapOfTextures)["number_3"]);
			break;
		case 4:
			currentTile.LoadNumTexture((*ptrToMapOfTextures)["number_4"]);
			break;
		case 5:
			currentTile.LoadNumTexture((*ptrToMapOfTextures)["number_5"]);
			break;
		case 6:
			currentTile.LoadNumTexture((*ptrToMapOfTextures)["number_6"]);
			break;
		case 7:
			currentTile.LoadNumTexture((*ptrToMapOfTextures)["number_7"]);
			break;
		case 8:
			currentTile.LoadNumTexture((*ptrToMapOfTextures)["number_8"]);
			break;
		default:
			break;
		}

	}

	/*while (numMinesToGive > (short) 0) {
		for (size_t i = 0; i < listOfTiles.size(); i++) {
			short randNum = random(1, 2);
			cout << "Random num: " << randNum << endl;
			if (randNum == 1) {
				Tile& currentTile = listOfTiles.at(i);

				if (currentTile.GetHasMine() == false) {
					cout << "Giving a mine" << endl;
					currentTile.AddMine();
					numMinesToGive--;
					cout << "Num mines remaining to give: " << numMinesToGive << endl;
				}
				else {
					cout << "This tile has a mine: " << i << " Bool Value: " << currentTile.GetHasMine() << endl;
					cout << "Num mines remaining to give: " << numMinesToGive << endl;
				}
			}
			else {

			}
		}
	}*/
}

Tile* Board::FindClickedUITile(float x, float y) {
	for (auto i = mapOfUITiles.begin(); i != mapOfUITiles.end(); i++) {
		if (i->second.GetCurrentSprite().getGlobalBounds().contains(x, y)) {
			return &(i->second);
		}
 	}
	return nullptr;
}

void Board::IncRevealedCount() {
	revealedCount++;
	if (revealedCount == (tileNumber - mineCount)) {
		EndGame(*ptrToMapOfTextures, "victory");
	}
}

bool Board::GetGameOver() {
	return isGameOver;
}

void Board::TestGame(GameInfo* optionalGameInfoPtr) {
	revealedCount = 0;
	isGameOver = false;
	mineCount = optionalGameInfoPtr->mineCount;
	short numMinesToGive = 0;
	numMinesToGive = optionalGameInfoPtr->mineCount;
	Tile& smileyTile = GetUITile("faceUI");
	smileyTile.LoadTexture((*ptrToMapOfTextures)["face_happy"]);
	listOfTiles.clear();
	currentCounter.UpdateCounter(numMinesToGive);
	time_t timer;
	time(&timer);

	random_mt.seed(timer);
	//Create the tiles that can contain mines
	for (short i = 0; i < tileNumber; i++) {
		short row = i / columns;
		short column = i % columns;
		Tile newTile((*ptrToMapOfTextures)["tile_hidden"], row, column, (*ptrToMapOfTextures));
		listOfTiles.push_back(newTile);
	}

	//Load the mines into the tiles that can contain mines

	for (short i = 0; i < optionalGameInfoPtr->tileCount; i++) {
		Tile& currentTile = listOfTiles.at(i);
		if (optionalGameInfoPtr->listOfMines.at(i) == 1) {
			currentTile.AddMine();
		}
	}
	//Assigned the neibors to each tile if the neibor exists
	for (short i = 0; i < tileNumber; i++) {
		short row = i / columns;
		short column = i % columns;
		Tile& currentTile = listOfTiles.at(i);
		//Cardinal Direction Pointers
		Tile* NTile = nullptr;
		try {
			NTile = &(this->GetTile(row - 1, column));
		}
		catch (std::out_of_range e) {

		}

		Tile* STile = nullptr;
		try {
			STile = &(this->GetTile(row + 1, column));
		}
		catch (std::out_of_range e) {

		}

		Tile* ETile = nullptr;
		try {
			ETile = &(this->GetTile(row, column + 1));
		}
		catch (std::out_of_range e) {

		}

		Tile* WTile = nullptr;
		try {
			WTile = &(this->GetTile(row, column - 1));
		}
		catch (std::out_of_range e) {

		}

		//Ordinal Direction Pointers
		Tile* NETile = nullptr;
		try {
			NETile = &(this->GetTile(row - 1, column + 1));
		}
		catch (std::out_of_range e) {

		}

		Tile* SETile = nullptr;
		try {
			SETile = &(this->GetTile(row + 1, column + 1));
		}
		catch (std::out_of_range e) {

		}

		Tile* SWTile = nullptr;
		try {
			SWTile = &(this->GetTile(row + 1, column - 1));
		}
		catch (std::out_of_range e) {

		}

		Tile* NWTile = nullptr;
		try {
			NWTile = &(this->GetTile(row - 1, column - 1));
		}
		catch (std::out_of_range e) {

		}

		currentTile.AddNeighbor("N", NTile);
		currentTile.AddNeighbor("S", STile);
		currentTile.AddNeighbor("E", ETile);
		currentTile.AddNeighbor("W", WTile);
		currentTile.AddNeighbor("NE", NETile);
		currentTile.AddNeighbor("SE", SETile);
		currentTile.AddNeighbor("SW", SWTile);
		currentTile.AddNeighbor("NW", NWTile);
		switch (currentTile.GetNumNeighborsWithMines()) {
		case 1:
			currentTile.LoadNumTexture((*ptrToMapOfTextures)["number_1"]);
			break;
		case 2:
			currentTile.LoadNumTexture((*ptrToMapOfTextures)["number_2"]);
			break;
		case 3:
			currentTile.LoadNumTexture((*ptrToMapOfTextures)["number_3"]);
			break;
		case 4:
			currentTile.LoadNumTexture((*ptrToMapOfTextures)["number_4"]);
			break;
		case 5:
			currentTile.LoadNumTexture((*ptrToMapOfTextures)["number_5"]);
			break;
		case 6:
			currentTile.LoadNumTexture((*ptrToMapOfTextures)["number_6"]);
			break;
		case 7:
			currentTile.LoadNumTexture((*ptrToMapOfTextures)["number_7"]);
			break;
		case 8:
			currentTile.LoadNumTexture((*ptrToMapOfTextures)["number_8"]);
			break;
		default:
			break;
		}

	}
}