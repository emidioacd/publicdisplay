#pragma once

#include "ofMain.h"
#include "mIcon.h"
#define MARGIN 60
#define MARGINBETWEENTHUMBNAIL 30
#define SIZE_G 100
#include <sstream>

#define SSTR( x ) dynamic_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()
class Gallery {
public:
	Gallery(){}
	~Gallery(){}
	void setup(int galleryWidth);
	void update();
	void draw();
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	string mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void drawFrame(int wmargin, int hmargin, int index, ofVideoPlayer movie);
	void gotMessage(ofMessage msg);
	void scroll();
	ofVideoPlayer getVideoLoaded();
	ofDirectory dir;
	vector<ofVideoPlayer> movies;
	vector<mIcon> thumbnailsImg;

private:
	int width;
	int getIndexMoviePressed(int x, int y);
	void moveThumbnail(int key);
	void swapThumbnails(int t1, int t2);
	int thumbnailSelected;
	int items;
	int totalSize;
	int numThumbnails;
	int numberOfMovies;
	int first;
	int galleryWidth;
	int galleryHeight;

};
