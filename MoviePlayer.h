#pragma once
#include "ofMain.h"
#include "ofxUI.h"
#define MARGIN 40
#define MAX_SLIDER_VALUE 100.0
class MoviePlayer
{
public:
	MoviePlayer(void);
	~MoviePlayer(void);
	void setup(int topBarHeight);
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
	void movieToPlayer(string movie);
	ofVideoPlayer getMovieLoaded();	
	bool isMovieLoaded();
	ofxUICanvas *gui;   	
	void guiEvent(ofxUIEventArgs &e);
    bool drawPadding; 
	float red, green, blue;
    ofImage middle; 
private:
	int playerPosX;
	int playerPosY;
	bool hasMovieLoaded;
	ofDirectory dir;
	ofVideoPlayer movie;
	ofxUISlider* slider;

	int playerWidth;
	int playerHeight;
	int sliderHeight;

	
};

