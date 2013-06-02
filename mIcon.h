#pragma once
#include "ofMain.h"

class mIcon
{
public:
	mIcon(void);
	~mIcon(void);

	int getX();
	int getY();
	ofImage getImage();

	void setX(int value);
	void setY(int value);
	void setImage(ofImage value);
	void setWidth(int value);
	void setHeight(int value);
	bool isOnImage(int valX, int valY);
private:
	int x;
	int y;
	int width;
	int height;
    ofImage image;
	
};

