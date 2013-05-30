#include "testApp.h"

const int margin = 40;
const int size = 200;
const int galleryWidth = 500;
const int GALLERY = 0;
const int TIMELINE = 1;

void testApp::setup(){
	ofBackground(ofColor::black);
	mode = GALLERY;
	if(mode==GALLERY){
		player.setup();
	}
	gallery.setup(galleryWidth);
	changeButtonX=ofGetWidth()-100;
	changeButtonY=ofGetHeight()-100;
	changeButtonWidth=50;
	changeButtonHeight=20;
}

void testApp::update(){
	if(mode==GALLERY){
		gallery.update();
	}else if(mode == TIMELINE)
		timeline.update();
	player.update();
}

void testApp::draw(){
	drawChangeButton();
	if(mode==GALLERY){
		gallery.draw();
	}else if(mode == TIMELINE)
		timeline.draw();
	player.draw();
}

void testApp::keyPressed(int key){
	if(mode==GALLERY){
		gallery.keyPressed(key);
	}else if(mode == TIMELINE)
		timeline.keyPressed(key);
	
	player.keyPressed(key);
}
void testApp::keyReleased(int key){}
void testApp::mouseMoved(int x, int y){}
void testApp::mouseDragged(int x, int y, int button){}
void testApp::mousePressed(int x, int y, int button){
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
		//timeline.setMovie(player.getMovieLoaded());
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