#include "testApp.h"

const int margin = 45;
const int size = 200;
const int galleryWidth = 500;
const int GALLERY = 0;
const int TIMELINE = 1;

void testApp::setup(){
	ofBackground(ofColor::black);

	changeButtonX=ofGetWidth()-100;
	changeButtonY=ofGetHeight()-100;
	changeButtonWidth=50;
	topBarHeight=50;
	int windowHeight = ofGetWindowHeight();
	int windowWidth = ofGetWindowWidth();

	//Botoes top Timeline|Gallery
    guiSidebar = new ofxUICanvas(0, 0, (windowWidth/2), topBarHeight);
	timelineButton = guiSidebar->addLabelButton("TIMELINE", false, (windowWidth/2)-10, topBarHeight-10, 0, 0);

    guiSidebarGallery = new ofxUICanvas((windowWidth/2), 0, (windowWidth/2), topBarHeight);
	galleryButton = guiSidebarGallery->addLabelButton("GALLERY", true, (windowWidth/2)-10, topBarHeight-10, (windowWidth/2), 0);

	ofAddListener(guiSidebar->newGUIEvent, this, &testApp::guiEvent);
	ofAddListener(guiSidebarGallery->newGUIEvent, this, &testApp::guiEvent);

	mode = GALLERY;
	if(mode==GALLERY){
		player.setup(topBarHeight);
	}
	gallery.setup(galleryWidth);
}

void testApp::update(){
	if(mode==GALLERY){
		gallery.update();
	}else if(mode == TIMELINE)
		timeline.update();
	player.update();
}

void testApp::draw(){
	if(mode==GALLERY){
		gallery.draw();
	}else if(mode == TIMELINE)
		timeline.draw();
	player.draw();
}

void testApp::keyPressed(int key){
	if(mode==GALLERY)
		gallery.keyPressed(key);
	else if(mode == TIMELINE)
		timeline.keyPressed(key);
	player.keyPressed(key);
}
void testApp::keyReleased(int key){}
void testApp::mouseMoved(int x, int y){
        gallery.mouseMoved(x,y);
}
void testApp::mouseDragged(int x, int y, int button){}
void testApp::mousePressed(int x, int y, int button){
	if(mode==GALLERY){
			string movieToPlayer = gallery.mousePressed(x,y,button);
			if(movieToPlayer.compare("")!=0)
				player.movieToPlayer(movieToPlayer);
	}
}
void testApp::mouseReleased(int x, int y, int button){}
void testApp::windowResized(int w, int h){}
void testApp::gotMessage(ofMessage msg){}
void testApp::dragEvent(ofDragInfo dragInfo){}

void testApp::guiEvent(ofxUIEventArgs &e){
	string name = e.widget->getName();
	if(name == "TIMELINE"){
		mode = TIMELINE;
		timelineButton->setValue(true);
		galleryButton->setValue(false);
	}
	else if(name == "GALLERY"){
		mode = GALLERY;
		galleryButton->setValue(true);
		timelineButton->setValue(false);
	}
}
void testApp::exit(){
	cout<<"gtfouuuut"<<endl;
	cout<<"gtfouuuut"<<endl;
	cout<<"gtfouuuut"<<endl;
	gallery.saveGallery();
}

