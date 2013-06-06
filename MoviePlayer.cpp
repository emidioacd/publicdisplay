#include "MoviePlayer.h"

MoviePlayer::MoviePlayer(void){
	hasMovieLoaded = false;}
MoviePlayer::~MoviePlayer(void){}

void MoviePlayer::setup(int topBarHeigh){
	float dim = 20;
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = 320-xInit;
	sliderHeight= dim;

	//Player
	playerPosX = 600;
	playerPosY = topBarHeigh + 50;
	playerHeight = 400;//ofGetWindowHeight()-topBarHeigh-sliderHeight;
	playerWidth = playerHeight;

	//slider
	int sliderY= playerPosY+playerHeight;
    gui = new ofxUICanvas(playerPosX, sliderY, playerWidth, sliderHeight);
	gui->setVisible(false);
    slider = gui->addSlider("RED", 0.0, MAX_SLIDER_VALUE, red, playerWidth-10, sliderHeight-10);
	slider->setVisible(false);
    ofAddListener(gui->newGUIEvent, this, &MoviePlayer::guiEvent);


}
void MoviePlayer::update(){
	if(hasMovieLoaded){
		movie.update();
		filter.update();
    }



}
void MoviePlayer::draw(){
	ofPushStyle();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofSetColor(255);
    //middle.getTextureReference().drawSubsection(ofGetWidth()*.5, ofGetHeight()*.5, middle.getWidth()*10, middle.getHeight(), middle.getWidth(),0,1,middle.getHeight());
	ofPopStyle();
	ofSetColor(ofColor::white);
	if(hasMovieLoaded){
		movie.draw(playerPosX, playerPosY, playerWidth, playerHeight);
        filter.draw();

		float currentF = (float)movie.getCurrentFrame();
		int totalF = (float)movie.getTotalNumFrames();
		//regra tres simples
		float val = (currentF*MAX_SLIDER_VALUE)/totalF;
		slider->setValue(val);
	}
}






void MoviePlayer::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName();
	int kind = e.widget->getKind();

	if(name == "RED")	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		int val = (int)slider->getScaledValue();
		//regra tres simples
		int pos = (val*movie.getTotalNumFrames())/MAX_SLIDER_VALUE;
		movie.setFrame(pos);
	}
	if(name == "PLAY")
        cout << "EH MAMACUDI !!" << endl;

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

    int movieHeight = movie.getHeight();
	int movieWidth = movie.getWidth();

    filter.setup(playerPosX, playerPosY, movieHeight,movieWidth, playerHeight,playerWidth, movie);

	hasMovieLoaded = true;
	slider->setVisible(true);
	gui->setVisible(true);
	ofLog(OF_LOG_NOTICE, "Player > Video carregado: "+movieToPlay);
	ofLog(OF_LOG_NOTICE, "Player > Video carregado: "+movieToPlay);
	movie.play();
}

ofVideoPlayer MoviePlayer::getMovieLoaded(){
	return movie;
}

bool MoviePlayer::isMovieLoaded(){
	return hasMovieLoaded;
}
