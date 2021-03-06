#pragma once
#include "ofMain.h"
#include "ofxUI.h"
#include "ofxXmlSettings.h"
#include "ofxCvHaarFinder.h"
#include "Filter.h"
#include "Movie.h"


#define MARGIN 40

const string xmlFile = "settings.xml";

class PlayList
{
public:
	PlayList(void){}
	~PlayList(void){}
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
	void movieToPlayer(int index);
    bool loadPlaylist();



private:

	ofDirectory dir;

	int playerWidth;
	int playerHeight;
    int camWidth;
	int camHeight;

	int currentMovie;
	int numberOfMovies;
    bool active;

    int wait;

    vector<Movie> movies;
    ofVideoPlayer moviePub;
    ofVideoGrabber vidGrabber;
    ofxCvHaarFinder finder;

};

