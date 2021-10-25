#pragma once

#include "SDL.h"
#include "SDL_ttf.h"

#include "TextureManager.h"
#include "CPlayer.h"
#include "CBall.h"
#include "CBricks.h"
#include "state.h"
#include "define.h"

#include <iostream>
#include <string>

//#define nbLineBrick 3
//#define nbColBrick 7


class CGame {
private:
	bool bRunning;
	bool bRoundStart;
	bool bEndGame;

	SDL_Window* pWindow;
	SDL_Renderer* pRenderer;

	CTextureManager textureManager;

	CPlayer player;
	CBall ball;

	CBricks bricks[nbLineBrick][nbColBrick];

	int score;
	int PV;
public:
	//Constructeur
	CGame();

	//Destructeur
	~CGame();

	//Framework
	bool init(const char* title, int xpos, int ypos, int WWIDTH, int WHEIGHT, int flags);
	void render(int WWIDTH, int WHEIGHT);
	void update(int WWIDTH, int WHEIGHT);
	void handleEvents(int WWIDTH, int WHEIGHT);
	void clean();

	//Accesseurs
	bool getBRunning();

	//Mutateurs
	void setBRunning(bool bRunning);

	//win condition
	bool checkWinCondition();

	//restart
	void restartGame(int WWIDTH, int WHEIGHT);

protected:

};