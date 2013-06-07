
#pragma once
#include "ofMain.h"
#include "ofxUI.h"

const int sharperMatrix[3][3] =  {-1,-1,-1,-1,9,-1,-1,-1,-1};
const int blurWeight = 25;
const int edgesMatrix[3][3] =  {-1,-1,-1,-1,8,-1,-1,-1,-1};



class Filter
{
public:
	Filter(void){}
	~Filter(void){}
	void setup(int x, int y, int h, int w, int ph, int pw, ofVideoPlayer m);
	void update();
	void draw();
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);


	void negativeFilter();
	void sharperFilter();
	void blurFilter();
	void bwFilter();
	void greyFilter();
	void edgesFilter();


	int truncColor(int color);


private:
	void guiEvent(ofxUIEventArgs &e);
    int movieHeight;
	int movieWidth;
	int posX;
	int posY;
	int playerWidth;
	int playerHeight;
    ofVideoPlayer movie;
    unsigned char * videoFilter;
    ofTexture videoTexture;

    unsigned char * pixels;
};
