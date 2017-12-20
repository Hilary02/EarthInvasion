#include "Rect.h"



Rect::Rect(int w,int h,double amp) {
	//leftX = x;
	//leftY = y;
	width = (int)(w*amp);
	height = (int)(h*amp);
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
	int MyLeftX = leftX;
	int MyLeftY = leftY;
	int MyRightX = leftX + width;
	int MyRightY = leftY + height;
	int OneLeftX = r.getLeftX();
	int OneLeftY = r.getLeftY();
	int OneRightX = r.getLeftX() + r.getWidth();
	int OneRightY = r.getLeftY() + r.getHeight();

	if ((r.getLeftX() < leftX + width) &&
		(r.getLeftX() + r.getWidth() > leftX) &&
		(r.getLeftY() < leftY + height) &&
		(r.getLeftY() + r.getHeight() > leftY)) {
		/*“–‚½‚Á‚Ä‚¢‚éê‡‚É‚±‚Ì•”•ª‚ªÀs‚³‚ê‚Ü‚·*/
		return true;
	}
	return false;
}