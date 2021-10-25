#include "CBricks.h"

CBricks::CBricks()
{
	bDestroyed = false;
}

CBricks::~CBricks()
{
}

void CBricks::AfficheLog() const
{
	CObject::AfficheLog();
}

bool CBricks::getBDestroyed()
{
	return bDestroyed;
}

std::string CBricks::getColor()
{
	return color;
}

void CBricks::setBDestroyed(bool bDestroyed)
{
	this->bDestroyed = bDestroyed;
}

//GOAL	: Set a color depending on the number
void CBricks::setColor(int nbLine)
{
	switch (nbLine) {
	case 0:
		color = "pinkBrick";
		break;
	case 1:
		color = "redBrick";
		break;
	case 2:
		color = "blueBrick";
		break;
	case 3:
		color = "greenBrick";
		break;
	case 4:
		color = "yellowBrick";
		break;
	default:
		color = "yellowBrick";
		break;
	}
}

//GOAL	: Depending on the color of the brick, it give a different point
int CBricks::addToScore()
{
	if (this->color == "yellowBrick") {
		return 1;
	}
	else if (this->color == "greenBrick") {
		return 2;
	}
	else if (this->color == "blueBrick") {
		return 3;
	}
	else if (this->color == "redBrick") {
		return 4;
	}
	else if (this->color == "pinkBrick") {
		return 5;
	}
	return 0;
}

