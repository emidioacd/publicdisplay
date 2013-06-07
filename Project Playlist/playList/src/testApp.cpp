
#include "testApp.h"

const int margin = 45;
const int size = 200;

void testApp::setup(){
	ofBackground(ofColor::black);

	playlist.setup();

}

void testApp::update(){
	playlist.update();
}

void testApp::draw(){

	playlist.draw();
}

void testApp::keyPressed(int key){
    playlist.keyPressed(key);
}
void testApp::keyReleased(int key){}
void testApp::mouseMoved(int x, int y){
}
void testApp::mouseDragged(int x, int y, int button){}
void testApp::mousePressed(int x, int y, int button){

}
void testApp::mouseReleased(int x, int y, int button){}
void testApp::windowResized(int w, int h){}
void testApp::gotMessage(ofMessage msg){}
void testApp::dragEvent(ofDragInfo dragInfo){}


void testApp::exit(){

}

