#include "testApp.h"

const int margin = 40;
const int size = 200;
const int galleryWidth = 500;
const int GALLERY = 0;
const int TIMELINE = 1;

void testApp::setup(){
	mode = GALLERY;
	if(mode==GALLERY){
		player.setup();
		gallery.setup(galleryWidth);
	}
	changeButtonX=ofGetWidth()-100;
	changeButtonY=ofGetHeight()-100;
	changeButtonWidth=50;
	changeButtonHeight=20;
}

void testApp::update(){
	if(mode==GALLERY){
		player.update();
		gallery.update();
	}
}

void testApp::draw(){
	drawChangeButton();
	if(mode==GALLERY){
		player.draw();
		gallery.draw();
	}
}

void testApp::keyPressed(int key){
	if(mode==GALLERY){
		player.keyPressed(key);
		gallery.keyPressed(key);
	}
}
void testApp::keyReleased(int key){}
void testApp::mouseMoved(int x, int y){}
void testApp::mouseDragged(int x, int y, int button){}

void testApp::mousePressed(int x, int y, int button){
		string result;
		ostringstream convert;
		ostringstream convert2;
		ostringstream convert3;
		ostringstream convert4;
		convert << x ;
		convert2 << y ;
		convert3 << changeButtonX ;
		convert4 << changeButtonY ;
		
		ofLog(OF_LOG_NOTICE, "x: "+convert.str());
		ofLog(OF_LOG_NOTICE, "y: "+convert2.str());
		ofLog(OF_LOG_NOTICE, "button x: "+convert3.str());
		ofLog(OF_LOG_NOTICE, "button y: "+convert4.str());
	if(isToChangeButton(x, y, button)){
		changeMode();
	}
	else{
		if(mode==GALLERY){
			if(gallery.movieWasPressed(x,y,button)){
				string movieToPlayer = gallery.mousePressed(x,y,button);
				player.movieToPlayer(movieToPlayer);
			}
		}
	}
}

void testApp::mouseReleased(int x, int y, int button){}
void testApp::windowResized(int w, int h){}
void testApp::gotMessage(ofMessage msg){}
void testApp::dragEvent(ofDragInfo dragInfo){}


void testApp::changeMode(){
	if(mode==TIMELINE)
		mode = GALLERY;
	else if(mode == GALLERY)
		mode = TIMELINE;
}
bool testApp::isToChangeButton(int x, int y, int button){
	return (x >changeButtonX && x < changeButtonX +changeButtonWidth && y < changeButtonY && y > changeButtonY-changeButtonHeight);
}
void testApp::drawChangeButton(){
	string modeButton;
	
	if(mode==TIMELINE)
		modeButton = "Gallery";
	else
		if(mode==GALLERY)
			modeButton = "Timeline";
	ofSetColor(ofColor::red);
	ofDrawBitmapString(modeButton, changeButtonX , changeButtonY);
}