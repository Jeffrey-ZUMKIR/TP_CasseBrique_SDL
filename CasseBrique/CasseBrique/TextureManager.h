#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include <iostream>
#include <map>

class CTextureManager {
private:
	std::map<std::string, SDL_Texture*> m_textureMap;

	TTF_Font* font;
	SDL_Color color;
public:
	//Constructeur
	CTextureManager();

	//Destructeur
	~CTextureManager();

	//Accesseurs
	TTF_Font* getFont();
	SDL_Color getColor();

	//Mutateurs
	void setFont(TTF_Font* font);
	void setColor(SDL_Color color);

	//Load image
	bool loadPNG(std::string fileName, std::string id, SDL_Renderer* pRenderer);

	//Load text
	bool loadText(std::string fileName, std::string id, SDL_Renderer* pRenderer);

	// draw
	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
protected:
};