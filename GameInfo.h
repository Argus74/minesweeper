#pragma once
#include <vector>
using namespace std;
struct GameInfo {
	int windowWidth;
	int windowHeight;
	int mineCount;
	int tileCount;
	int boardWidth;
	int tileHeight;
	int boardHeight;
	vector<int> listOfMines;
};