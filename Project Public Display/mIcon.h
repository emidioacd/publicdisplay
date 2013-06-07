#pragma once
#include "ofMain.h"
#include "ofxXmlSettings.h"
class mIcon
{
public:
	mIcon(void){}
	~mIcon(void){}

	int getX();
	int getY();
	int getWidth();
	int getHeight();
	ofImage getImage();
	int getFirstFrame();
	string getUrl();
    void setup(int x, int y, int w, int h,string url);
	void update();
	void draw();

	void setX(int value);
	void setY(int value);
	void setImage(ofImage value);
	void setWidth(int value);
	void setHeight(int value);
	bool isOnImage(int valX, int valY);
	void setFirstFrame(int frame);
	void setUrl(string url);
	void mouseMoved(int x, int y);

    int x;
	int y;
	int width;
	int height;


private:

	int firstFrame;
	int wait;
	int currentFrame;
	int totalFrames;
	string url;
	ofVideoPlayer movie;
	ofImage image;
	bool hover;



};

