#include "CPlayer.h"

CPlayer::CPlayer() :CObject()
{
	state = eState::IDLE;
	speed = 0;
}

CPlayer::~CPlayer()
{
}

eState CPlayer::getState()
{
	return state;
}

int CPlayer::getSpeed()
{
	return speed;
}

void CPlayer::setState(eState state)
{
	this->state = state;
}

void CPlayer::setSpeed(int speed)
{
	this->speed = speed;
}

void CPlayer::move(int WWIDTH)
{
	switch (state) {
	case eState::LEFT:
		setX(getX() - speed);
		break;
	case eState::RIGHT:
		setX(getX() + speed);
		break;
	default:
		break;
	}

	if (getX() < 0) {
		setX(0);
	}
	else if (getX()+getW() > WWIDTH) {
		setX(WWIDTH-getW());
	}
}

void CPlayer::AfficheLog() const
{
	CObject::AfficheLog();
}
