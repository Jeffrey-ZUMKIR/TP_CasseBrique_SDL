#include "CObject.h"

CObject::CObject()
{
	rectPos = { 0,0,0,0 };
}

CObject::~CObject()
{
}

SDL_Rect CObject::getRect()
{
	return rectPos;
}

int CObject::getX()
{
	return rectPos.x;
}

int CObject::getY()
{
	return rectPos.y;
}

int CObject::getW()
{
	return rectPos.w;
}

int CObject::getH()
{
	return rectPos.h;
}

void CObject::setRect(int x, int y, int w, int h)
{
	rectPos.x = x;
	rectPos.y = y;
	rectPos.w = w;
	rectPos.h = h;
}

void CObject::setX(int x)
{
	rectPos.x = x;
}

void CObject::setY(int y)
{
	rectPos.y = y;
}

void CObject::setW(int w)
{
	rectPos.w = w;
}

void CObject::setH(int h)
{
	rectPos.h = h;
}

void CObject::AfficheLog() const
{
	std::cout << rectPos.x << " " << rectPos.y << " " << rectPos.w << " " << rectPos.h << " " << std::endl;
}
