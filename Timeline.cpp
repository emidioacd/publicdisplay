#include "Timeline.h"

void Timeline::setup(){
	//previewBtn =  new MyButton(20, 20, 2, 2, "");

}

void Timeline::update(){
		movie.update();
}

void Timeline::draw(){
	//previewBtn.draw();
}
void Timeline::keyPressed(int key){
	setFullScreen();
}

void Timeline::setMovie(ofVideoPlayer movieToLoad){
	movie = movieToLoad;
}

void Timeline::setFullScreen(){
	ofToggleFullscreen();
}

void Timeline::mousePressed(int x, int y, int button){
	//if(previewBtn.wasPressed(x, y))
		//setFullScreen();
}