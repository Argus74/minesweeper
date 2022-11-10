#include "Tile.h"
#include "Board.h"
#include <iostream>


Tile::Tile() {
	hasMine = false;
}

void Tile::OnClick(sf::Mouse::Button buttonType, map<string, sf::Texture>& mapOfTextures, Board* gameBoard)
{
	const sf::Texture* ptrToTexture = currentSprite.getTexture();

	if (buttonType == sf::Mouse::Button::Left && hasFlag == false) {
		if (ptrToTexture == &mapOfTextures["tile_hidden"] && (gameBoard->GetGameOver() == false)) {
			if (hasMine == true) {
				gameBoard->EndGame(mapOfTextures, "defeat");
			}
			else {
				RecursiveReveal(mapOfTextures, gameBoard);
			}
			
		}
		else if(ptrToTexture == &mapOfTextures["face_happy"] || ptrToTexture == &mapOfTextures["face_lose"] || ptrToTexture == &mapOfTextures["face_win"]) {
			gameBoard->NewGame();
		}
		else if (ptrToTexture == &mapOfTextures["debug"] && (gameBoard->GetGameOver() == false)) {
			vector<Tile>& listOfTiles = gameBoard->GetListOfTiles();
			for (size_t i = 0; i < listOfTiles.size(); i++) {
				listOfTiles.at(i).ToggleDebug();
			}
		}
		else if (ptrToTexture == &mapOfTextures["test_1"]) {
			gameBoard->TestGame(gameBoard->test1);
		}
		else if (ptrToTexture == &mapOfTextures["test_2"]) {
			gameBoard->TestGame(gameBoard->test2);
		}
		else if (ptrToTexture == &mapOfTextures["test_3"]) {
			gameBoard->TestGame(gameBoard->test3);
		}
	}
	else if (buttonType == sf::Mouse::Button::Right) {
		if (ptrToTexture == &mapOfTextures["tile_hidden"] && (gameBoard->GetGameOver() == false)) {
			if (hasFlag == false) {
				hasFlag = true;
				gameBoard->GetMineCounter().Decrement();
			}
			else {
				hasFlag = false;
				gameBoard->GetMineCounter().Increment();
			}

		}
	}
}

Tile::Tile(sf::Texture& tileTexture, short row, short column, map<string, sf::Texture>& mapOfTextures) {
	x = (float)(column * 32 + 16);
	y = (float)(row * 32 + 16);
	currentSprite.setOrigin(16.0f, 16.0f);
	currentSprite.setPosition(x, y);
	currentSprite.setTexture(tileTexture);
	const sf::Texture* ptrToTexture = currentSprite.getTexture();
	if (ptrToTexture == &mapOfTextures["tile_hidden"]) {
		flagSprite.setOrigin(16.0f, 16.0f);
		flagSprite.setPosition(x, y);
		flagSprite.setTexture(mapOfTextures["flag"]);
		
		mineSprite.setOrigin(16.0f, 16.0f);
		mineSprite.setPosition(x, y);
		mineSprite.setTexture(mapOfTextures["mine"]);
	}
	else if (ptrToTexture == &mapOfTextures["face_happy"] || ptrToTexture == &mapOfTextures["face_lose"] || ptrToTexture == &mapOfTextures["face_win"]) {
		
	}

}

void Tile::LoadTexture(sf::Texture& newTexture) {
	currentSprite.setTexture(newTexture);
}

sf::Sprite& Tile::GetCurrentSprite() {
	return currentSprite;
}

void Tile::DrawTile(sf::RenderWindow& currentWindow, map<string, sf::Texture>& mapOfTextures) {
	currentWindow.draw(currentSprite);
	const sf::Texture* ptrToTexture = currentSprite.getTexture();
	if (ptrToTexture == &mapOfTextures["tile_hidden"]) {
		
		if (hasFlag == true) {
			currentWindow.draw(flagSprite);
		}
		if ((hasMine == true) && (isDebugMode == true)) {
			currentWindow.draw(mineSprite);
		}
		
	}
	else if (ptrToTexture == &mapOfTextures["tile_revealed"]) {

		if (hasFlag == true) {
			currentWindow.draw(flagSprite);
		}

		if (hasMine == true) {
			currentWindow.draw(mineSprite);
		}
		else {
			if (numNeighborsWithMines > 0) {
				currentWindow.draw(numSprite);
			}
		}
	}
}

void Tile::AddMine() {
	hasMine = true;
}

bool Tile::GetHasMine() {
	return hasMine;
}

void Tile::AddNeighbor(string direction, Tile* newNeighbor) {
	if (newNeighbor == nullptr) {
	}
	else {
		if (direction == "N") {
			N = newNeighbor;
		}
		else if (direction == "NE") {
			NE = newNeighbor;
		}
		else if (direction == "E") {
			E = newNeighbor;
		}
		else if (direction == "SE") {
			SE = newNeighbor;
		}
		else if (direction == "S") {
			S = newNeighbor;
		}
		else if (direction == "SW") {
			SW = newNeighbor;
		}
		else if (direction == "W") {
			W = newNeighbor;
		}
		else if (direction == "NW") {
			NW = newNeighbor;
		}
		if (newNeighbor->GetHasMine() == true) {
			numNeighborsWithMines++;
		}
	}

}

void Tile::RecursiveReveal(map<string, sf::Texture>& mapOfTextures, Board* gameBoard) {
	if (currentSprite.getTexture() == &mapOfTextures["tile_revealed"] || hasFlag == true || hasMine == true) {
		return;
	}
	else {
		gameBoard->IncRevealedCount();
		currentSprite.setTexture(mapOfTextures["tile_revealed"]);
		if (numNeighborsWithMines > 0) {
			return;
		}
		else {
			if (N != nullptr) {
				(*N).RecursiveReveal(mapOfTextures, gameBoard);
			}
			if (NE != nullptr) {
				(*NE).RecursiveReveal(mapOfTextures, gameBoard);
			}
			if (E != nullptr) {
				(*E).RecursiveReveal(mapOfTextures, gameBoard);
			}
			if (SE != nullptr) {
				(*SE).RecursiveReveal(mapOfTextures, gameBoard);
			}
			if (S != nullptr) {
				(*S).RecursiveReveal(mapOfTextures, gameBoard);
			}
			if (SW != nullptr) {
				(*SW).RecursiveReveal(mapOfTextures, gameBoard);
			}
			if (W != nullptr) {
				(*W).RecursiveReveal(mapOfTextures, gameBoard);
			}
			if (NW != nullptr) {
				(*NW).RecursiveReveal(mapOfTextures, gameBoard);
			}
		}
	}
}

void Tile::LoadNumTexture(sf::Texture& newNumTexture) {
	numSprite.setOrigin(16.0f, 16.0f);
	numSprite.setPosition(x, y);
	numSprite.setTexture(newNumTexture);
}

short Tile::GetNumNeighborsWithMines() {
	return numNeighborsWithMines;
}

void Tile::ToggleHasFlag(bool newSetting) {
	hasFlag = newSetting;
}

bool Tile::GetHasFlag() {
	return hasFlag;
}

void Tile::ToggleDebug() {
	if (isDebugMode == true) {
		isDebugMode = false;
	}
	else {
		isDebugMode = true;
	}
}

void Tile::SetDebug(bool newSetting) {
	isDebugMode = newSetting;
}