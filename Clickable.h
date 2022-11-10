#pragma once
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>
#include <map>


class Board;
using namespace std;
class Clickable
{
public:
	virtual void OnClick(sf::Mouse::Button buttonType, map<string, sf::Texture>& mapOfTextures, Board* gameBoard) = 0;
};

