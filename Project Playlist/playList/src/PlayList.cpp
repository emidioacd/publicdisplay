#include "PlayList.h"

void PlayList::setup(){
	//Player

	playerWidth = 320;
	playerHeight = 240;//ofGetWindowHeight()-topBarHeigh-sliderHeight;
    currentMovie = 0;
    wait = 100;

    dir.listDir("movies");
    loadPlaylist();


	camWidth 		= 320;
	camHeight 		= 240;

	vidGrabber.setVerbose(true);
	vidGrabber.setDeviceID(1);
	vidGrabber.setDesiredFrameRate(24);
	vidGrabber.initGrabber(camWidth,camHeight);

	ofSetVerticalSync(true);

	finder.setup("haarcascade_frontalface_default.xml");

    int h = movies[currentMovie].getHeight();
    int w = movies[currentMovie].getWidth();


    //Play da class Movie
    movies[currentMovie].play();
}
//--------------------------------------------------------------

void PlayList::update(){

    vidGrabber.update();
    ofImage img = ofImage();
    img.setFromPixels(vidGrabber.getPixelsRef());

    finder.findHaarObjects(img);
    active = finder.blobs.size() > 0;
    cout<<currentMovie<<endl;
    if(movies[currentMovie].stopped()){

           movieToPlayer(currentMovie+1);
    }


    if(!active) movies[currentMovie].pause(true);
    else movies[currentMovie].pause(false);



    movies[currentMovie].update();

}


//--------------------------------------------------------------
void PlayList::draw(){
    movies[currentMovie].draw();

    vidGrabber.draw(playerWidth+(MARGIN*2),MARGIN,playerWidth, playerHeight);
    ofNoFill();

    for(int i = 0; i < finder.blobs.size(); i++) {
		ofRectangle cur = finder.blobs[i].boundingRect;
		ofRect(cur.x+playerWidth+MARGIN*2, cur.y+MARGIN, cur.width, cur.height);
    }
}

//--------------------------------------------------------------
void PlayList::keyPressed(int key){

	if(key==OF_KEY_LEFT){
	    movies[currentMovie].stop();
        movieToPlayer(currentMovie-1);
    }
    else if(key==OF_KEY_RIGHT){
        movies[currentMovie].stop();
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

		movies.assign(numberOfMovies, Movie());

		cout << "numTags: " << numberOfMovies << endl;

		for(int i = 0 ; i<numberOfMovies ; i++)
		{
			settings.pushTag("video", i);
			string url = settings.getValue("url","");

			ofVideoPlayer movieAux= ofVideoPlayer();
			movieAux.loadMovie(url);

			int h = movieAux.getHeight();
			int w = movieAux.getWidth();

			int firstFrame = settings.getValue("firstFrame",1);
			int lastFrame = settings.getValue("lastFrame",1);
            settings.pushTag("filters");

            int numFilters = settings.getNumTags("filter");

            movies[i].setup(movieAux,numFilters, firstFrame, lastFrame);

			for(int j = 0; j < numFilters; j++){
                settings.pushTag("filter", j);
                string filterName = settings.getValue("name","");
                int ff = settings.getValue("firstFrame",1);
                int lf = settings.getValue("lastFrame",1);

                //Adiciona ao vector de filtros do video
                movies[i].addFilter(j,filterName,ff, lf);
                settings.popTag();
			}
			settings.popTag();
			settings.popTag();
		}
			settings.popTag();
	}
	return hasFile;
}






