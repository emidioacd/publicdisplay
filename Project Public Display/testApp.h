#pragma once

#include "ofMain.h"
#include "gallery.h"
#include "MoviePlayer.h"
#include "Timeline.h"
#include "ofxUI.h"
#include "ofxXmlSettings.h"

#define MARGIN 40
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
	void exit();
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
private:
	Gallery gallery;
	void changeMode();
	Timeline timeline;
	bool isToChangeButton(int x, int y, int button);
	int mode;
	int changeButtonX;
	int changeButtonY;
	int changeButtonWidth;
	int changeButtonHeight;
	ofxUICanvas* guiSidebar;
	MoviePlayer player;
	ofxUICanvas* guiSidebarGallery;
	ofxUILabelButton* timelineButton;
	ofxUILabelButton* galleryButton;
	void guiEvent(ofxUIEventArgs &e);
	int topBarHeight;
	//ofDirectory dir;
	//vector<ofVideoPlayer> movies;
};
