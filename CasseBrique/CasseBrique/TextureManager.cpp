#include "TextureManager.h"

CTextureManager::CTextureManager()
{
	font = NULL;
	color = { 255, 255, 255 };
}

CTextureManager::~CTextureManager()
{
}

TTF_Font* CTextureManager::getFont()
{
	return font;
}

SDL_Color CTextureManager::getColor()
{
	return color;
}

void CTextureManager::setFont(TTF_Font* font)
{
	this->font = font;
}

void CTextureManager::setColor(SDL_Color color)
{
	this->color = color;
}

//GOAL	: Load a PNG image with an ID in the list
bool CTextureManager::loadPNG(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if (pTempSurface == 0){
		return false;
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);

	if (pTexture != 0){
		m_textureMap[id] = pTexture;
		return true;
	}
	return false;
}

//GOAL	: Load a text with an ID in the list
bool CTextureManager::loadText(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTempSurface = TTF_RenderText_Solid(font, fileName.c_str(), color);
	if (pTempSurface == 0) {
		return false;
	}
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);
	// everything went ok, add the texture to our list
	if (pTexture != 0) {
		m_textureMap[id] = pTexture;
		return true;
	}
	// reaching here means something went wrong
	return false;
}

//GOAL	: Display the texture
void CTextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect destRect;

	destRect.w = width;
	destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], NULL, &destRect, 0, 0, flip);
}
