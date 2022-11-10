#include "MineCounter.h"
#include <iostream>
using namespace std;
//Still need to handle case when mine goes negative

MineCounter::MineCounter() {
	count = 0;
}

MineCounter::MineCounter(sf::Texture& digitsTexture, short row, short column, short initCount) {
	count = initCount;
	float yPos = 32 * row + 16.0f;
	float xPosNeg = 32 * column - 21;
	float xPos1 = 32 * column;
	float xPos2 = 32 * column + 21;
	float xPos3 = 32 * column + 42;
	left.setTexture(digitsTexture);
	left.setTextureRect(sf::IntRect(0, 0, 21, 32));
	left.setOrigin(10.5f, 16.0f);
	left.setPosition(xPos1, yPos);

	middle.setTexture(digitsTexture);
	middle.setTextureRect(sf::IntRect(0, 0, 21, 32));
	middle.setOrigin(10.5f, 16.0f);
	middle.setPosition(xPos2, yPos);

	right.setTexture(digitsTexture);
	right.setTextureRect(sf::IntRect(0, 0, 21, 32));
	right.setOrigin(10.5f, 16.0f);
	right.setPosition(xPos3, yPos);
	
	negative.setTexture(digitsTexture);
	negative.setTextureRect(sf::IntRect(10 * 21, 0, 21, 32));
	negative.setOrigin(10.5f, 16.0f);
	negative.setPosition(xPosNeg, yPos);
	UpdateCounter(count);
}

sf::Sprite& MineCounter::GetSpriteDigit(string pos) {
	if (pos == "left") {
		return left;
	}
	else if (pos == "middle") {
		return middle;
	}
	else {
		return right;
	}
}

void MineCounter::UpdateCounter(short initCount) {
	count = initCount;
	if (initCount < 0) {
		isNegative = true;
		initCount = initCount * -1;
	}
	else {
		isNegative = false;
	}
	short digit;
	short digitPos = 0;
	do {
		digit = initCount % 10;
		initCount = initCount / 10;
		int XPosOfCorner = digit * 21;
		digitPos++;
		switch (digitPos)
		{
		case 1:
			right.setTextureRect(sf::IntRect(XPosOfCorner, 0, 21, 32));
			middle.setTextureRect(sf::IntRect(0, 0, 21, 32));
			left.setTextureRect(sf::IntRect(0, 0, 21, 32));
			break;
		case 2:
			middle.setTextureRect(sf::IntRect(XPosOfCorner, 0, 21, 32));
			left.setTextureRect(sf::IntRect(0, 0, 21, 32));
			break;
		case 3:
			left.setTextureRect(sf::IntRect(XPosOfCorner, 0, 21, 32));
			break;
		default:
			break;
		} 
	} while (initCount != 0);
}

short MineCounter::Increment() {
	count++;
	UpdateCounter(count);
	return count;
}

short MineCounter::Decrement() {
	count--;
	UpdateCounter(count);
	return count;
}

bool MineCounter::GetIsNegative() {
	return isNegative;
}