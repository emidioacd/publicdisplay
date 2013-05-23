#pragma once

#include "ofMain.h"
#include "gallery.h"
#include "MoviePlayer.h"

class testApp : public ofBaseApp{
	public:

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

		Gallery gallery;
		MoviePlayer player;
private:
	void testApp::changeMode();
	bool testApp::isToChangeButton(int x, int y, int button);
	void testApp::drawChangeButton();
	int mode;
	int changeButtonX;
	int changeButtonY;
	int changeButtonWidth;
	int changeButtonHeight;
//		ofDirectory dir;
//		vector<ofVideoPlayer> movies;
};
