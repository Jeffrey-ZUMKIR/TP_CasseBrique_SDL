#pragma once

#include "SDL.h"

#include <iostream>

class CObject {
private:
	SDL_Rect rectPos;
public:
	//Constructeur
	CObject();

	//Destructeur
	~CObject();

	//Accesseurs
	SDL_Rect getRect();
	int getX();
	int getY();
	int getW();
	int getH();

	//Mutateurs
	void setRect(int x, int y, int w, int h);
	void setX(int x);
	void setY(int y);
	void setW(int w);
	void setH(int h);

	//set class abstraite
	virtual void AfficheLog() const = 0;

protected:
};