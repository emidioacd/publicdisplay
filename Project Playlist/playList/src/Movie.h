
#pragma once
#include "ofMain.h"
#include "ofxUI.h"
#include "ofxXmlSettings.h"

#include "Filter.h"


const int posX = 40;
const int posY = 40;

class Movie
{
public:
	Movie(void){}
	~Movie(void){}
	void setup(ofVideoPlayer movie, int numFilters, int firstFrame, int lastFrame);
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
	void pause(bool p);
	void play();
	void stop();
    bool stopped();
    int getHeight();
    int getWidth();
    void addFilter(int index,string filterName,int ff, int lf);

private:

    string url;
	int playerWidth;
	int playerHeight;
	int w;
	int h;

    ofVideoPlayer movie;

    int firstFrame;
    int lastFrame;

    vector<Filter> filters;




};

