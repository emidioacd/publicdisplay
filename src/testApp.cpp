#include "testApp.h"

const int margin = 40;
const int size = 200;

void testApp::setup(){
	gallery.setup();
}

void testApp::update(){
	gallery.update();
}

void testApp::draw(){
	gallery.draw();
}

void testApp::keyPressed(int key){}
void testApp::keyReleased(int key){}
void testApp::mouseMoved(int x, int y){}
void testApp::mouseDragged(int x, int y, int button){}

void testApp::mousePressed(int x, int y, int button){
	gallery.mousePressed(x,y,button);
}

void testApp::mouseReleased(int x, int y, int button){}
void testApp::windowResized(int w, int h){}
void testApp::gotMessage(ofMessage msg){}
void testApp::dragEvent(ofDragInfo dragInfo){}

