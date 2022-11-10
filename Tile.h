#pragma once
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include "Clickable.h"


using namespace std;
class Board;


class Tile : Clickable
{
private:
	float x = 0;
	float y = 0;
	sf::Sprite currentSprite;
	sf::Sprite mineSprite;
	sf::Sprite flagSprite;
	sf::Sprite numSprite;
	bool hasMine = false;
	bool revealed = false;
	bool hasFlag = false;
	bool isDebugMode = false;
	short numNeighborsWithMines = 0;
	Tile* N = nullptr;
	Tile* NE = nullptr;
	Tile* E = nullptr;
	Tile* SE = nullptr;
	Tile* S = nullptr;
	Tile* SW = nullptr;
	Tile* W = nullptr;
	Tile* NW = nullptr;
public:
	Tile();
	void OnClick(sf::Mouse::Button buttonType, map<string, sf::Texture>& mapOfTextures, Board* gameBoard) override;
	Tile(sf::Texture& tileTexture, short row, short column, map<string, sf::Texture>& mapOfTextures);
	void LoadTexture(sf::Texture& newTexture);
	void LoadNumTexture(sf::Texture& newNumTexture);
	void DrawTile(sf::RenderWindow& currentWindow, map<string, sf::Texture>& mapOfTextures);
	sf::Sprite& GetCurrentSprite();
	void AddMine();
	bool GetHasMine();
	bool GetHasFlag();
	void ToggleHasFlag(bool newSetting);
	void ToggleDebug();
	void SetDebug(bool newSetting);
	void AddNeighbor(string direction, Tile* newNeighbor);
	void RecursiveReveal(map<string, sf::Texture>& mapOfTextures, Board* gameBoard);
	short GetNumNeighborsWithMines();
};

