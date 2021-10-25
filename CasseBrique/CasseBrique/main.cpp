#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "CGame.h"
#include "CObject.h"
#include "CPlayer.h"

const int WWIDTH = 900;
const int WHEIGHT = 640;

int main(int argc, char** argv) {

	CGame game;

	game.init("Game", 100, 100, WWIDTH, WHEIGHT, 0);

	while (game.getBRunning()) {
		game.handleEvents(WWIDTH, WHEIGHT);
		game.update(WWIDTH, WHEIGHT);
		game.render(WWIDTH, WHEIGHT);
		SDL_Delay(1000 / 60);
	}
	game.clean();


	return 0;
}