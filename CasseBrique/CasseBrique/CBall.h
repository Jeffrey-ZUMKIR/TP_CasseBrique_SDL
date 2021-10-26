#pragma once

#include "CObject.h"
#include "CPlayer.h"
#include "CBricks.h"
#include "define.h"

class CBall : public CObject {
private:
	int speedX, speedY;
	int maxBallSpeed;
public:
	//Constructeur
	CBall();

	//Destructeur
	~CBall();

	//Accesseurs
	int getSpeedX();
	int getSpeedY();
	int getMaxSpeed();

	//Mutateurs
	void setSpeedX(int speedX);
	void setSpeedY(int speedY);
	void setMaxSpeed(int maxSpeed);

	void checkPos(int WWIDTH, int WHEIGHT, CPlayer player, CBricks bricks[][nbColBrick], int *score, bool *bRoundStart, int* PV);
	void move(int WWIDTH, int WHEIGHT);

	void startRound(bool *bRoundStart);
	void followPlayer(CPlayer player);

	void AfficheLog() const override;

protected:

};