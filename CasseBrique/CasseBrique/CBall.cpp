#include "CBall.h"

#define PI 3.14159265
#define MAXBALLSPEED 8

CBall::CBall()
{
	speedX = 0;
	speedY = 0;
}

CBall::~CBall()
{
}

int CBall::getSpeedX()
{
	return speedX;
}

int CBall::getSpeedY()
{
	return speedY;
}

void CBall::setSpeedX(int speedX)
{
	this->speedX = speedX;
}

void CBall::setSpeedY(int speedY)
{
	this->speedY = speedY;
}

void CBall::checkPos(int WWIDTH, int WHEIGHT, CPlayer player, CBricks bricks[][nbColBrick], int *score, bool *bRoundStart, int *PV)
{
	//Check if the ball is in collision with the top of the window
	if (getY() <= 0) {
		speedY = speedY * -1;
	}
	//Check the collision of the left and right side of the window
	if (getX() <= 0 || getX() + getW() >= WWIDTH) {
		speedX = speedX * -1;
	}
	//Check if the ball touched the bottom of the window
	if (getY() + getH() >= WHEIGHT) {
		*PV -= 1;
		*bRoundStart = true;
	}

	//Check if the ball is in collision with the player 
	if (this->getY() >= WHEIGHT - 100) {
		if (this->getX() <= player.getX() + player.getW() && this->getX() >= player.getX() && this->getY() + this->getH() >= player.getY() && this->getY() <= player.getY() + player.getH()) {
			if (this->speedY > 0) {
				//Change the direction of the ball direction depending of where the collision is happening
				//Get the distance between the collision and the middle of the player 1 (get a number between -75 and 75
				float relativeIntersect = (player.getX() + (player.getW() / static_cast<float>(2))) - (this->getX() + (this->getW() / static_cast<float>(2)));
				//Get a position normalized around -1 and 1
				float normalizedRelativeIntersectionY = (relativeIntersect / (player.getW() / static_cast<float>(2)));
				//Calculate the bounce angle 
				float bounceAngle = static_cast<float>(normalizedRelativeIntersectionY * 4 * PI / 12);

				//Give the new speed for the ball
				this->speedX = static_cast<int>(MAXBALLSPEED * -sin(bounceAngle));
				this->speedY = static_cast<int>(MAXBALLSPEED * -cos(bounceAngle));
			}
		}
	}
	else if (this->getY() <= nbLineBrick*50) {
		for (int n_i = 0; n_i < nbLineBrick; n_i++) {
			for (int n_j = 0; n_j < nbColBrick; n_j++) {
				if (bricks[n_i][n_j].getBDestroyed() == false) {
					if (this->getX() + (this->getW() / 2) >= bricks[n_i][n_j].getX()
						&& this->getX() + (this->getW() / 2) <= bricks[n_i][n_j].getX() + bricks[n_i][n_j].getW()) {
						//Collision under bricks
						if (this->getY() <= bricks[n_i][n_j].getY() + bricks[n_i][n_j].getH()
							&& this->getY() >= bricks[n_i][n_j].getY() + (bricks[n_i][n_j].getH() / 10)) {
							this->speedY *= -1;
							bricks[n_i][n_j].setBDestroyed(true);
							*score += bricks[n_i][n_j].addToScore();
						}
						//Collision top bricks
						else if (this->getY() + this->getH() >= bricks[n_i][n_j].getY()
							&& this->getY() + this->getH() <= bricks[n_i][n_j].getY() + (bricks[n_i][n_j].getH() / 10)) {
							this->speedY *= -1;
							bricks[n_i][n_j].setBDestroyed(true);
							*score += bricks[n_i][n_j].addToScore();
						}
					}

					if (this->getY() + (this->getH() / 2) >= bricks[n_i][n_j].getY()
						&& this->getY() + (this->getH() / 2) <= bricks[n_i][n_j].getY() + bricks[n_i][n_j].getH()) {
						//Collision left side bricks
						if (this->getX() + this->getW() >= bricks[n_i][n_j].getX()
							&& this->getX() + this->getW() <= bricks[n_i][n_j].getX() + (bricks[n_i][n_j].getW() / 10)) {
							this->speedX *= -1;
							bricks[n_i][n_j].setBDestroyed(true);
							*score += bricks[n_i][n_j].addToScore();
						}
						//Collision right side bricks
						else if (this->getX() <= bricks[n_i][n_j].getX() + bricks[n_i][n_j].getW()
							&& this->getX() >= bricks[n_i][n_j].getX() + (bricks[n_i][n_j].getW() / 10)) {
							this->speedX *= -1;
							bricks[n_i][n_j].setBDestroyed(true);
							*score += bricks[n_i][n_j].addToScore();
						}
					}
				}
			}
		}
	}

	this->move(WWIDTH, WHEIGHT);
}

//GOAL	: Move the ball depending of his speed
void CBall::move(int WWIDTH, int WHEIGHT)
{
	setX(getX() + speedX);
	setY(getY() + speedY);

	if (getX() < 0) {
		setX(0);
	}
	else if (getX() + getW() > WWIDTH) {
		setX(WWIDTH - getW());
	}

	if (getY() < 0) {
		setY(0);
	}
	else if (getY() + getH() > WHEIGHT) {
		setY(WHEIGHT - getH());
	}
}

void CBall::startRound(bool *bRoundStart)
{
	*bRoundStart = false;
}

//GOAL	: Kepp the ball next to the player
void CBall::followPlayer(CPlayer player)
{
	this->setX(player.getX() + (player.getW() / 2) - (this->getW() / 2));
	this->setY(player.getY() - this->getH());
}

void CBall::AfficheLog() const
{
	CObject::AfficheLog();
}
