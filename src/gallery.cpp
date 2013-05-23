#include "gallery.h"

void Gallery::setup(){
	dir.listDir("movies");
	dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order
	ofSetVerticalSync(true);
	if( dir.size() ){
		movies.assign(dir.size(), ofVideoPlayer());
	}

	for(int i = 0; i < (int)dir.size(); i++){
		movies[i].loadMovie(dir.getPath(i));
	}
	ofBackground(ofColor::white);
}

void Gallery::update(){
	for(int i = 0; i < (int)dir.size(); i++){
		movies[i].update();
	}
}

void Gallery::draw(){
	int items = ofGetWindowWidth()/(SIZE + MARGIN);

	if(dir.size() == 0){
		ofSetColor(ofColor::gray);
		string no_videos = "No videos!";
		ofDrawBitmapString(no_videos, ofGetWidth()/2 , ofGetHeight()/2);
	}
	int hmargin = MARGIN;
	int wmargin = MARGIN;
	for(int i = 0; i < (int)dir.size(); i++){
		if(i!= 0 && i%items == 0){
			hmargin+=SIZE + MARGIN;
			wmargin = MARGIN;
		}else if(i!=0) wmargin+=SIZE + MARGIN;
		ofSetColor(ofColor::white);
		movies[i].draw(wmargin, hmargin, SIZE, SIZE);
	}
}

void Gallery::keyPressed(int key){}
void Gallery::keyReleased(int key){}
void Gallery::mouseMoved(int x, int y){}
void Gallery::mouseDragged(int x, int y, int button){}

void Gallery::mousePressed(int x, int y, int button){
	int items = ofGetWindowWidth()/(SIZE + MARGIN);

	int totalSize = SIZE + MARGIN;
	int line = (y/totalSize);
	int index = (x/totalSize)+line*items;

	int column = index%items;
	int xInMargin = ((column+1)*totalSize)-SIZE;
	int yInMargin = ((line+1)*totalSize)-SIZE;

	if(x >= xInMargin && y >= yInMargin){
		if(index < dir.size()){
			if(button == 2){
				movies[index].stop();
			} else if(movies[index].isPaused()){
					movies[index].setPaused(false);
					movies[index].play();
			} else movies[index].setPaused(true);
		}
	}
}

void Gallery::mouseReleased(int x, int y, int button){}
void Gallery::windowResized(int w, int h){}
void Gallery::gotMessage(ofMessage msg){}
void Gallery::dragEvent(ofDragInfo dragInfo){}
