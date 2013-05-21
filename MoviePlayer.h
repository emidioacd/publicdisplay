#pragma once
#include "ofMain.h"
#define MARGIN 40
#define SIZE 500
class MoviePlayer
{
public:
	MoviePlayer(void);
	~MoviePlayer(void);
	void setup();
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
	bool hasMovieLoaded;
	ofDirectory dir;
	ofVideoPlayer movie;
};

