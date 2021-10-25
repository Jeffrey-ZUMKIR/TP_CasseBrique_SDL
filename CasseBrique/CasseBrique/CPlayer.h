#pragma once

#include "CObject.h"
#include "state.h"

class CPlayer : public CObject {
private:
	eState state;
	int speed;
public:
	//Constructeur
	CPlayer();

	//Destructeur
	~CPlayer();

	//Accesseurs
	eState getState();
	int getSpeed();

	//Mutateurs
	void setState(eState state);
	void setSpeed(int speed);

	//movement
	void move(int WWIDTH);

	void AfficheLog() const override;
protected:

};