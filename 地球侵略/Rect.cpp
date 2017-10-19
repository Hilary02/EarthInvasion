#include "Rect.h"



Rect::Rect(int x, int y, int w, int h) {
	leftX = x;
	leftY = y;
	width = w;
	height = h;
}

Rect::Rect()
{
}


Rect::~Rect()
{
}

int Rect::getLeftX()
{
	return leftX;
}

int Rect::getLeftY()
{
	return leftY;
}

int Rect::getWidth() {
	return width;
}

int Rect::getHeight() {
	return height;
}

bool Rect::isHit(Rect r) {
	if ((r.getLeftX() < leftX + width) &&
		(r.getLeftX() + r.getWidth() > leftX) &&
		(r.getLeftY() < leftY + height) &&
		(r.getLeftY() + r.getHeight() > leftY)) {
		/*“–‚½‚Á‚Ä‚¢‚éê‡‚É‚±‚Ì•”•ª‚ªÀs‚³‚ê‚Ü‚·*/
		return true;
	}
	return false;
}