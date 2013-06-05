#pragma once
#include "ofMain.h"

class mIcon
{
public:
	mIcon(void);
	~mIcon(void);
	
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	ofImage getImage();
	int getFirstFrame();
	string getUrl();

	void setX(int value);
	void setY(int value);
	void setImage(ofImage value);
	void setWidth(int value);
	void setHeight(int value);
	bool isOnImage(int valX, int valY);
	void setFirstFrame(int frame);
	void setUrl(string url);
private:
	int x;
	int y;
	int width;
	int height;
	int firstFrame;
	string url;
    ofImage image;
	
};

