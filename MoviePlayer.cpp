#include "MoviePlayer.h"

MoviePlayer::MoviePlayer(void){
	hasMovieLoaded = false;}
MoviePlayer::~MoviePlayer(void){}

void MoviePlayer::setup(){
}
void MoviePlayer::update(){
	if(hasMovieLoaded)
		movie.update();
}
void MoviePlayer::draw(){
	ofSetColor(ofColor::white);
	if(hasMovieLoaded)
		movie.draw(500, MARGIN, SIZE, SIZE);
}

void MoviePlayer::keyPressed(int key){
	//if(key==OF_KEY_LEFT)
		//movie.setSpeed(-1);
	//else if(key==OF_KEY_RIGHT)
		//movie.setSpeed(2);
	//else
		if(key=='s')
		movie.stop();
	else if(key=='p')
		if(movie.isPaused())
			movie.setPaused(false);
		else 
			movie.setPaused(true);
}
void MoviePlayer::keyReleased(int key){}
void MoviePlayer::mouseMoved(int x, int y){}
void MoviePlayer::mouseDragged(int x, int y, int button){}
void MoviePlayer::mousePressed(int x, int y, int button){}

void MoviePlayer::mouseReleased(int x, int y, int button){}
void MoviePlayer::windowResized(int w, int h){}
void MoviePlayer::gotMessage(ofMessage msg){}
void MoviePlayer::dragEvent(ofDragInfo dragInfo){}


void MoviePlayer::movieToPlayer(string movieToPlay){
	
	movie.loadMovie(movieToPlay);
	hasMovieLoaded = true;
	ofLog(OF_LOG_NOTICE, "Player > Video carregado: "+movieToPlay);
	movie.play();
}