#include "CGame.h"


CGame::CGame()
{
	bRunning = true;
	bRoundStart = true;
	bEndGame = false;
	pWindow = NULL;
	pRenderer = NULL;
	score = 0;
	PV = 0;
}

CGame::~CGame()
{
}

bool CGame::init(const char* title, int xpos, int ypos, int WWIDTH, int WHEIGHT, int flags)
{
	// attempt to initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0){
		std::cout << "SDL init success\n";
		// init the window
		pWindow = SDL_CreateWindow(title, xpos, ypos, WWIDTH, WHEIGHT, flags);
		// window initsuccess
		if (pWindow != 0) {
			std::cout << "window creation success\n";
			pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
			// renderer init success
			if (pRenderer != 0) {
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(pRenderer, 255,255,255,255);
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false; // renderer init fail
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // SDL init fail
	}

	//init TTF
	if (TTF_Init() == -1)
	{
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}

	//Game is on
	bRunning = true;

	//Start of round
	bRoundStart = true;

	//End of game
	bEndGame = false;

	//Set score
	score = 0;

	//Set PV
	PV = 3;

	//Set font
	textureManager.setFont(TTF_OpenFont("ArialCE.ttf", 50));

	//Load PNG and Text
	textureManager.loadPNG("./Assets/Player.png", "player", pRenderer);
	textureManager.loadPNG("./Assets/Ball.png", "ball", pRenderer);
	textureManager.loadPNG("./Assets/RedBrick.png", "redBrick", pRenderer);
	textureManager.loadPNG("./Assets/YellowBrick.png", "yellowBrick", pRenderer);
	textureManager.loadPNG("./Assets/GreenBrick.png", "greenBrick", pRenderer);
	textureManager.loadPNG("./Assets/BlueBrick.png", "blueBrick", pRenderer);
	textureManager.loadPNG("./Assets/PinkBrick.png", "pinkBrick", pRenderer);
	textureManager.loadText("Press SPACE to start","startGame",pRenderer);
	textureManager.loadText(std::to_string(score), "score", pRenderer);
	textureManager.loadText("Score: " + std::to_string(score), "finalScore", pRenderer);
	textureManager.loadText("Press SPACE to restart", "endGame", pRenderer);

	//Set player
	player.setRect((WWIDTH/2)-75, WHEIGHT-20, 150, 20);
	player.setState(eState::IDLE);
	player.setSpeed(5);

	//Set ball
	ball.setRect((WWIDTH / 2) - 10, WHEIGHT - 100, 20, 20);
	ball.setSpeedX(8);
	ball.setSpeedY(8);

	//Set all the bricks
	for (int n_i = 0; n_i < nbLineBrick; n_i++) {
		for (int n_j = 0; n_j < nbColBrick; n_j++) {
			bricks[n_i][n_j].setBDestroyed(false);
			bricks[n_i][n_j].setColor(n_i);
			bricks[n_i][n_j].setRect(n_j * (WWIDTH / nbColBrick), n_i * 50, WWIDTH / nbColBrick, 50);
		}
	}

	std::cout << "init success\n";
}

void CGame::render(int WWIDTH, int WHEIGHT)
{
	//Background
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(pRenderer); // clear the renderer to the draw color

	//If begin of the round, show what to do
	if (bRoundStart && PV != 0) {
		textureManager.draw("startGame", (WWIDTH / 2) - 150, (3 * WHEIGHT) / 4, 300, 50, pRenderer);
	}

	//Draw player
	textureManager.draw("player",player.getX(), player.getY(), player.getW(), player.getH(),pRenderer);

	//If game not finished show the ball
	if (!bEndGame) {
		textureManager.draw("ball", ball.getX(), ball.getY(), ball.getW(), ball.getH(), pRenderer);
	}
	//Load and draw the final score
	else {
		textureManager.loadText("Score: " + std::to_string(score), "finalScore", pRenderer);
		textureManager.draw("finalScore", (WWIDTH / 2) - 100, (3 * WHEIGHT) / 4 - 100, 200, 50, pRenderer);
		textureManager.draw("endGame", (WWIDTH / 2) - 150, (3 * WHEIGHT) / 4, 300, 50, pRenderer);
	}
	
	//Draw all the bricks still alived
	for (int n_i = 0; n_i < nbLineBrick; n_i++) {
		for (int n_j = 0; n_j < nbColBrick; n_j++) {

			if (bricks[n_i][n_j].getBDestroyed() == false) {
				textureManager.draw(bricks[n_i][n_j].getColor(), bricks[n_i][n_j].getX(), bricks[n_i][n_j].getY(), bricks[n_i][n_j].getW(), bricks[n_i][n_j].getH(), pRenderer);
			}
		}
	}

	//Load and draw score
	textureManager.loadText(std::to_string(score), "score", pRenderer);
	textureManager.draw("score", 10, 10, 30, 30, pRenderer);
	
	SDL_RenderPresent(pRenderer); // draw to the screen
}

void CGame::update(int WWIDTH, int WHEIGHT)
{
	//Check win condition
	bEndGame = checkWinCondition();
	//Move player
	player.move(WWIDTH);
	//if begin of the round, ball follow the player
	if (bRoundStart) {
		ball.followPlayer(player);
	}
	else {
		//if not end of the game, ball move
		if (!bEndGame) {
			ball.checkPos(WWIDTH, WHEIGHT, player, bricks, &score, &bRoundStart, &PV);
		}
	}
	
}

void CGame::handleEvents(int WWIDTH, int WHEIGHT)
{
	SDL_Event event;
	if (SDL_PollEvent(&event)){
		switch (event.type){
		case SDL_QUIT:
			bRunning = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
			case SDLK_q:
				player.setState(eState::LEFT);
				break;
			case SDLK_RIGHT:
			case SDLK_d:
				player.setState(eState::RIGHT);
				break;
			case SDLK_SPACE:
				if (bRoundStart) {
					ball.startRound(&bRoundStart);
				}
				if (bEndGame) {
					//init("Game", 100, 100, WWIDTH, WHEIGHT, 0);
					restartGame(WWIDTH, WHEIGHT);
				}
			default:
				break;
			}
			break;
			//Input release
		case SDL_KEYUP:
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
			case SDLK_q:
			case SDLK_RIGHT:
			case SDLK_d:
				player.setState(eState::IDLE);
				break;
			break;
		}
		default:
			break;
		}
	}
}

void CGame::clean()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(pWindow);
	SDL_DestroyRenderer(pRenderer);
	TTF_Quit();
	SDL_Quit();

}

bool CGame::getBRunning()
{
	return bRunning;
}

void CGame::setBRunning(bool bRunning)
{
	this->bRunning = bRunning;
}

//GOAL	: Check if there is anymore lives or any more bricks
bool CGame::checkWinCondition()
{
	if (PV == 0) {
		return true;
	}
	for (int n_i = 0; n_i < nbLineBrick; n_i++) {
		for (int n_j = 0; n_j < nbColBrick; n_j++) {
			if (bricks[n_i][n_j].getBDestroyed() == false) {
				return false;
			}
		}
	}
	return true;
}

//Reset every variable
void CGame::restartGame(int WWIDTH, int WHEIGHT)
{
	//Start of round
	bRoundStart = true;

	//End of game
	bEndGame = false;

	//Set score
	score = 0;

	//Set PV
	PV = 3;

	//Set player
	player.setRect((WWIDTH / 2) - 75, WHEIGHT - 20, 150, 20);
	player.setState(eState::IDLE);
	player.setSpeed(5);

	//Set ball
	ball.setRect((WWIDTH / 2) - 10, WHEIGHT - 100, 20, 20);
	ball.setSpeedX(8);
	ball.setSpeedY(8);

	//Set all the bricks
	for (int n_i = 0; n_i < nbLineBrick; n_i++) {
		for (int n_j = 0; n_j < nbColBrick; n_j++) {
			bricks[n_i][n_j].setBDestroyed(false);
			bricks[n_i][n_j].setColor(n_i);
			bricks[n_i][n_j].setRect(n_j * (WWIDTH / nbColBrick), n_i * 50, WWIDTH / nbColBrick, 50);
		}
	}
}
