#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
//Still need to handle case when mine goes negative
class MineCounter
{
private:
	
	short count = 0;
	bool isNegative = false;
public:
	sf::Sprite left;
	sf::Sprite middle;
	sf::Sprite right;
	sf::Sprite negative;
	MineCounter();
	MineCounter(sf::Texture& digitsTexture, short row, short column, short initCount);
	sf::Sprite& GetSpriteDigit(string pos);
	void UpdateCounter(short initCount);
	short Increment();
	short Decrement();
	bool GetIsNegative();

};

