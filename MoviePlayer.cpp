#include "MoviePlayer.h"

MoviePlayer::MoviePlayer(void){
	hasMovieLoaded = false;}
MoviePlayer::~MoviePlayer(void){}

void MoviePlayer::setup(){
	float dim = 24; 
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING; 
    float length = 320-xInit; 
    gui = new ofxUICanvas(PLAYERPOSX, MARGIN+SIZE, SIZE, dim+10);
	gui->setVisible(false);
	
	//ofImage img;
	//img.loadImage("images/play_button.png");
	//gui->addImage("PLAY", &img, 20.0, 20.0);
    slider = gui->addSlider("RED", 0.0, MAX_SLIDER_VALUE, red, SIZE-7, dim);
	slider->setVisible(false);
    ofAddListener(gui->newGUIEvent, this, &MoviePlayer::guiEvent);	
}
void MoviePlayer::update(){
	if(hasMovieLoaded)
		movie.update();
}
void MoviePlayer::draw(){
	ofPushStyle(); 
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);     
    ofSetColor(255);
    middle.getTextureReference().drawSubsection(ofGetWidth()*.5, ofGetHeight()*.5, middle.getWidth()*10, middle.getHeight(), middle.getWidth(),0,1,middle.getHeight());
	ofPopStyle();
	ofSetColor(ofColor::white);
	if(hasMovieLoaded){
		movie.draw(PLAYERPOSX, MARGIN, SIZE, SIZE);
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
		cout << "total: " << movie.getTotalNumFrames() << endl;
        cout << "currentFrame: " << movie.getCurrentFrame() << endl;
		int val = (int)slider->getScaledValue();
		//regra tres simples
		int pos = (val*movie.getTotalNumFrames())/MAX_SLIDER_VALUE;
		movie.setFrame(pos);
        cout << "value: " << pos << endl; 
        cout << "currentFrame: " << movie.getCurrentFrame() << endl; 
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
	hasMovieLoaded = true;
	slider->setVisible(true);
	gui->setVisible(true);
	ofLog(OF_LOG_NOTICE, "Player > Video carregado: "+movieToPlay);
	movie.play();
}

ofVideoPlayer MoviePlayer::getMovieLoaded(){
	return movie;
}

bool MoviePlayer::isMovieLoaded(){
	return hasMovieLoaded;
}