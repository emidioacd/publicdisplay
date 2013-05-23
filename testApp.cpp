#include "testApp.h"

const int margin = 40;
const int size = 200;
const int galleryWidth = 500;

void testApp::setup(){
	player.setup();
	gallery.setup(galleryWidth);
}

void testApp::update(){
	player.update();
	gallery.update();
}

void testApp::draw(){
	player.draw();
	gallery.draw();
}

void testApp::keyPressed(int key){
		//player.keyPressed(key);
	gallery.keyPressed(key);
}
void testApp::keyReleased(int key){}
void testApp::mouseMoved(int x, int y){}
void testApp::mouseDragged(int x, int y, int button){}

void testApp::mousePressed(int x, int y, int button){
	if(gallery.movieWasPressed(x,y,button)){
		string movieToPlayer = gallery.mousePressed(x,y,button);
		player.movieToPlayer(movieToPlayer);
	}
}

void testApp::mouseReleased(int x, int y, int button){}
void testApp::windowResized(int w, int h){}
void testApp::gotMessage(ofMessage msg){}
void testApp::dragEvent(ofDragInfo dragInfo){}

