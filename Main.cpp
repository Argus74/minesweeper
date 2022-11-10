#include "Tile.h"
#include "Board.h"
#include <iostream>
#include <fstream>
#include "MineCounter.h"
#include "GameInfo.h"
#include <SFML/Window/Mouse.hpp>




void LoadTextures(map<string, sf::Texture>& mapOfTextures) {
	sf::Texture debug;
	debug.loadFromFile("images/debug.png");
	sf::Texture digits;
	digits.loadFromFile("images/digits.png");
	sf::Texture face_happy;
	face_happy.loadFromFile("images/face_happy.png");
	sf::Texture face_lose;
	face_lose.loadFromFile("images/face_lose.png");
	sf::Texture face_win;
	face_win.loadFromFile("images/face_win.png");
	sf::Texture flag;
	flag.loadFromFile("images/flag.png");
	sf::Texture mine;
	mine.loadFromFile("images/mine.png");
	sf::Texture number_1;
	number_1.loadFromFile("images/number_1.png");
	sf::Texture number_2;
	number_2.loadFromFile("images/number_2.png");
	sf::Texture number_3;
	number_3.loadFromFile("images/number_3.png");
	sf::Texture number_4;
	number_4.loadFromFile("images/number_4.png");
	sf::Texture number_5;
	number_5.loadFromFile("images/number_5.png");
	sf::Texture number_6;
	number_6.loadFromFile("images/number_6.png");
	sf::Texture number_7;
	number_7.loadFromFile("images/number_7.png");
	sf::Texture number_8;
	number_8.loadFromFile("images/number_8.png");
	sf::Texture test_1;
	test_1.loadFromFile("images/test_1.png");
	sf::Texture test_2;
	test_2.loadFromFile("images/test_2.png");
	sf::Texture test_3;
	test_3.loadFromFile("images/test_3.png");
	sf::Texture tile_hidden;
	tile_hidden.loadFromFile("images/tile_hidden.png");
	sf::Texture tile_revealed;
	tile_revealed.loadFromFile("images/tile_revealed.png");
	mapOfTextures["debug"] = debug;
	mapOfTextures["digits"] = digits;
	mapOfTextures["face_happy"] = face_happy;
	mapOfTextures["face_lose"] = face_lose;
	mapOfTextures["face_win"] = face_win;
	mapOfTextures["flag"] = flag;
	mapOfTextures["mine"] = mine;
	mapOfTextures["number_1"] = number_1;
	mapOfTextures["number_2"] = number_2;
	mapOfTextures["number_3"] = number_3;
	mapOfTextures["number_4"] = number_4;
	mapOfTextures["number_5"] = number_5;
	mapOfTextures["number_6"] = number_6;
	mapOfTextures["number_7"] = number_7;
	mapOfTextures["number_8"] = number_8;
	mapOfTextures["test_1"] = test_1;
	mapOfTextures["test_2"] = test_2;
	mapOfTextures["test_3"] = test_3;
	mapOfTextures["tile_hidden"] = tile_hidden;
	mapOfTextures["tile_revealed"] = tile_revealed;
}

void RenderBoard(Board& boardToRender, sf::RenderWindow& currentWindow, map<string, sf::Texture>& mapOfTextures) {
	vector<Tile>& listOfTiles = boardToRender.GetListOfTiles();
	for (size_t i = 0; i < listOfTiles.size(); i++) {
		Tile& currentTile = listOfTiles.at(i);
		currentTile.DrawTile(currentWindow, mapOfTextures);
	}
	map<string, Tile>& mapOfUITiles = boardToRender.GetMapOfUITiles();
	map<string, Tile>::iterator mapIterator;
	for (mapIterator = mapOfUITiles.begin(); mapIterator != mapOfUITiles.end(); mapIterator++) {
		mapIterator->second.DrawTile(currentWindow, mapOfTextures);
	}

	currentWindow.draw(boardToRender.GetMineCounter().left);
	currentWindow.draw(boardToRender.GetMineCounter().middle);
	currentWindow.draw(boardToRender.GetMineCounter().right);
	if (boardToRender.GetMineCounter().GetIsNegative() == true) {
		currentWindow.draw(boardToRender.GetMineCounter().negative);
	}
	currentWindow.display();
}

int main() {
	string currentTestFile;
	ifstream fileReader;
	GameInfo newGameInfo;
	GameInfo testInfo1;
	GameInfo testInfo2;
	GameInfo testInfo3;
	string currentLine;
	fileReader.open("boards/config.cfg");

	getline(fileReader, currentLine);
	newGameInfo.windowWidth = stoi(currentLine) * 32;
	newGameInfo.boardWidth = stoi(currentLine);

	getline(fileReader, currentLine);
	newGameInfo.windowHeight = (stoi(currentLine) * 32) + 88;

	getline(fileReader, currentLine);
	newGameInfo.mineCount = stoi(currentLine);

	newGameInfo.boardWidth = newGameInfo.windowWidth / 32;
	newGameInfo.tileHeight = (newGameInfo.windowHeight - 88) / 32;
	newGameInfo.boardHeight = (newGameInfo.windowHeight) / 32;
	newGameInfo.tileCount = newGameInfo.boardWidth * newGameInfo.tileHeight;
	fileReader.close();
	
	fileReader.open("boards/testboard1.brd");
	testInfo1.windowWidth = newGameInfo.windowWidth;
	testInfo1.boardWidth = newGameInfo.boardWidth;
	testInfo1.windowHeight = newGameInfo.windowHeight;
	
	short board1MineCount = 0;
	char currentNumChar = 0;
	while (fileReader.get(currentNumChar)) {
		if (currentNumChar == 49) {
			board1MineCount++;
			testInfo1.listOfMines.push_back(1);
		}
		else if (currentNumChar == 48){
			testInfo1.listOfMines.push_back(0);
		}
	}
	fileReader.close();

	testInfo1.mineCount = board1MineCount;
	testInfo1.boardWidth = newGameInfo.boardWidth;
	testInfo1.boardHeight = newGameInfo.boardHeight;
	testInfo1.tileCount = newGameInfo.tileCount;
	testInfo1.windowWidth = newGameInfo.windowWidth;
	testInfo1.boardWidth = newGameInfo.boardWidth;
	testInfo1.windowHeight = newGameInfo.windowHeight;

	fileReader.open("boards/testboard2.brd");
	testInfo2.windowWidth = newGameInfo.windowWidth;
	testInfo2.boardWidth = newGameInfo.boardWidth;
	testInfo2.windowHeight = newGameInfo.windowHeight;

	short board2MineCount = 0;
	currentNumChar = 0;
	while (fileReader.get(currentNumChar)) {
		if (currentNumChar == 49) {
			board2MineCount++;
			testInfo2.listOfMines.push_back(1);
		}
		else if (currentNumChar == 48) {
			testInfo2.listOfMines.push_back(0);
		}
	}
	fileReader.close();

	testInfo2.mineCount = board2MineCount;
	testInfo2.boardWidth = newGameInfo.boardWidth;
	testInfo2.boardHeight = newGameInfo.boardHeight;
	testInfo2.tileCount = newGameInfo.tileCount;
	testInfo2.windowWidth = newGameInfo.windowWidth;
	testInfo2.boardWidth = newGameInfo.boardWidth;
	testInfo2.windowHeight = newGameInfo.windowHeight;

	
	fileReader.close();

	fileReader.open("boards/testboard3.brd");
	testInfo3.windowWidth = newGameInfo.windowWidth;
	testInfo3.boardWidth = newGameInfo.boardWidth;
	testInfo3.windowHeight = newGameInfo.windowHeight;

	short board3MineCount = 0;
	currentNumChar = 0;
	while (fileReader.get(currentNumChar)) {
		if (currentNumChar == 49) {
			board3MineCount++;
			testInfo3.listOfMines.push_back(1);
		}
		else if (currentNumChar == 48) {
			testInfo3.listOfMines.push_back(0);
		}
	}
	fileReader.close();

	testInfo3.mineCount = board3MineCount;
	testInfo3.boardWidth = newGameInfo.boardWidth;
	testInfo3.boardHeight = newGameInfo.boardHeight;
	testInfo3.tileCount = newGameInfo.tileCount;
	testInfo3.windowWidth = newGameInfo.windowWidth;
	testInfo3.boardWidth = newGameInfo.boardWidth;
	testInfo3.windowHeight = newGameInfo.windowHeight;


	fileReader.close();

	sf::RenderWindow currentWindow(sf::VideoMode(newGameInfo.windowWidth, newGameInfo.windowHeight), "SFML window");
	sf::RenderWindow testWindow1;
	map<string, sf::Texture> mapOfTextures;
	LoadTextures(mapOfTextures);
	Board gameBoard(newGameInfo.boardHeight, newGameInfo.boardWidth, newGameInfo.tileCount, mapOfTextures, newGameInfo.mineCount, testInfo1, testInfo2, testInfo3, newGameInfo);

	while (currentWindow.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (currentWindow.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				currentWindow.close();
			else if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i mousePos = sf::Mouse::getPosition(currentWindow);
					short rowOfMouse = mousePos.y / 32;
					short columnOfMouse = mousePos.x / 32;
					try {
						Tile& objectThatWasLeftClicked = gameBoard.GetTile(rowOfMouse, columnOfMouse);
						objectThatWasLeftClicked.OnClick(sf::Mouse::Left, mapOfTextures, &gameBoard);
					}
					catch (exception e) {
						Tile* objectThatWasLeftClicked = gameBoard.FindClickedUITile(mousePos.x, mousePos.y);
						if (objectThatWasLeftClicked != nullptr) {
							objectThatWasLeftClicked->OnClick(sf::Mouse::Left, mapOfTextures, &gameBoard);
						}
					}
				}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					sf::Vector2i mousePos = sf::Mouse::getPosition(currentWindow);
					short rowOfMouse = mousePos.y / 32;
					short columnOfMouse = mousePos.x / 32;
					try {
						Tile& objectThatWasRightClicked = gameBoard.GetTile(rowOfMouse, columnOfMouse);
						objectThatWasRightClicked.OnClick(sf::Mouse::Right, mapOfTextures, &gameBoard);
					}
					catch (exception e) {

					}
				}
			}
		}

		// clear the window with black color
		currentWindow.clear(sf::Color::White);

		// draw everything here...
		// window.draw(...);

		// end the current frame
		RenderBoard(gameBoard, currentWindow, mapOfTextures);
	}
}