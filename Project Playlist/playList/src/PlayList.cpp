#include "PlayList.h"

void PlayList::setup(){
	//Player

	playerWidth = 320;
	playerHeight = 240;//ofGetWindowHeight()-topBarHeigh-sliderHeight;
    currentMovie = 0;
    wait = 100;
    active = true;

    dir.listDir("movies");
    loadPlaylist();
    moviePub = ofVideoPlayer();
    moviePub.loadMovie("movies/pub.mp4");
    /*
    Para testes sem XML

    if(!loadPlaylist()){
        dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order
        ofSetVerticalSync(true);
        if( dir.size() ){
            movies.assign(dir.size(), ofVideoPlayer());
        }
        numberOfMovies = dir.size();
        for(int i = 0 ; i < numberOfMovies ; i++){
            string path = dir.getPath(i);
            movies[i].loadMovie(path);
        }
    }*/
	camWidth 		= 320;	// try to grab at this size.
	camHeight 		= 240;

	vidGrabber.setVerbose(true);
	vidGrabber.setDeviceID(1);
	vidGrabber.setDesiredFrameRate(60);
	vidGrabber.initGrabber(camWidth,camHeight);

	ofSetVerticalSync(true);


	finder.setup("haarcascade_frontalface_default.xml");

    //moviePub.play();
    movies[currentMovie].play();
}
//--------------------------------------------------------------

void PlayList::update(){

    vidGrabber.update();
    ofImage img = ofImage();
    img.setFromPixels(vidGrabber.getPixelsRef());

        finder.findHaarObjects(img);
        active = finder.blobs.size() > 0;
        cout<<"FINDER: "<<finder.blobs.size()<<endl;
        wait  = 0;



    if(nextMovie()) currentMovie = (currentMovie+1)%(numberOfMovies-1);

    movies[currentMovie].update();
    if(!active)  movies[currentMovie].setPaused(true);
    else movies[currentMovie].setPaused(false);


    wait++;


}
bool PlayList::nextMovie(){
    return movies[currentMovie].getTotalNumFrames() == movies[currentMovie].getCurrentFrame();
}

//--------------------------------------------------------------
void PlayList::draw(){

    vidGrabber.draw(playerWidth+MARGIN*2,MARGIN);
    ofNoFill();

    for(int i = 0; i < finder.blobs.size(); i++) {
		ofRectangle cur = finder.blobs[i].boundingRect;
		ofRect(cur.x+playerWidth+MARGIN*2, cur.y+MARGIN, cur.width, cur.height);
	}

    movies[currentMovie].draw(MARGIN, MARGIN, playerWidth, playerHeight);

}



//--------------------------------------------------------------
void PlayList::keyPressed(int key){

	if(key==OF_KEY_LEFT){
				movieToPlayer(currentMovie-1);
    }
    else if(key==OF_KEY_RIGHT){
            movieToPlayer(currentMovie+1);
    }

}
void PlayList::keyReleased(int key){}
void PlayList::mouseMoved(int x, int y){}
void PlayList::mouseDragged(int x, int y, int button){}
void PlayList::mousePressed(int x, int y, int button){}

void PlayList::mouseReleased(int x, int y, int button){}
void PlayList::windowResized(int w, int h){}
void PlayList::gotMessage(ofMessage msg){}
void PlayList::dragEvent(ofDragInfo dragInfo){}

//--------------------------------------------------------------
void PlayList::movieToPlayer(int index){
    movies[currentMovie].stop();

    if(index < 0)
        currentMovie = numberOfMovies-1;
    else if(index > numberOfMovies-1)
        currentMovie = 0;
    else currentMovie = index;


	movies[currentMovie].play();
}

//--------------------------------------------------------------
bool PlayList::loadPlaylist(){
    ofxXmlSettings settings;
	bool hasFile = settings.loadFile(xmlFile);

	if(hasFile)
	{
		settings.pushTag("videos");

		int numTags = settings.getNumTags("video");
		numberOfMovies = numTags;

		movies.assign(numberOfMovies, ofVideoPlayer());
		cout << "numTags: " << numberOfMovies << endl;

		for(int i = 0 ; i<numberOfMovies ; i++)
		{
			settings.pushTag("video", i);
			string url = settings.getValue("url","");
			movies[i].loadMovie(url);
			cout << "url: " << settings.getValue("url","") << endl;
			settings.popTag();
		}

			settings.popTag();
	}
	return hasFile;
}






