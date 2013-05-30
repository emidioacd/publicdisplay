#include "gallery.h"

void Gallery::setup(int galleryWidth){
	thumbnailSelected=-1;
	width= galleryWidth;
	items = width/(SIZE + MARGIN);
	totalSize = SIZE + MARGIN;
	dir.listDir("movies");
	dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order
	ofSetVerticalSync(true);
	if( dir.size() ){
		movies.assign(dir.size(), ofVideoPlayer());
		thumbnailsImg.assign(dir.size(), ofImage());
	}
	numberOfMovies = dir.size();
	for(int i = 0; i < numberOfMovies; i++){
		movies[i].loadMovie(dir.getPath(i));
		cout<<dir.getPath(i)<<endl;
	}
	ofBackground(ofColor::white);
	first=true;
}
void Gallery::update(){
	for(int i = 0; i < (int)dir.size(); i++){
		movies[i].update();
	}
}

void Gallery::draw(){
	//int items = ofGetWindowWidth()/(SIZE + MARGIN);
	//if(first){
		//first=false;
		int items = width/(SIZE + MARGIN);
		if(dir.size() == 0){
			ofSetColor(ofColor::gray);
			string no_videos = "No videos!";
			ofDrawBitmapString(no_videos, ofGetWidth()/2 , ofGetHeight()/2);
		}
		int hmargin = MARGIN;
		int wmargin = MARGIN;
		
		for(int i = 0; i < numberOfMovies; i++){
			if(i!= 0 && i%items == 0){
				hmargin+=SIZE + MARGIN;
				wmargin = MARGIN;
			}else if(i!=0) wmargin+=SIZE + MARGIN;
			ofSetColor(ofColor::white);
			//movies[i].setFrame(20);
			if(thumbnailSelected==i)
				ofSetColor(ofColor::blue);
			drawFrame(wmargin, hmargin, i, movies[i]);
			//movies[i].draw(wmargin, hmargin, SIZE, SIZE);
		}
		first=false;
	//}
}
void Gallery::drawFrame(int wmargin, int hmargin, int index, ofVideoPlayer movie){
	if(first){
		thumbnailsImg[index].allocate(SIZE, SIZE, OF_IMAGE_COLOR);
		thumbnailsImg[index].setFromPixels(movie.getPixelsRef());
	}
	thumbnailsImg[index].draw(wmargin, hmargin, SIZE, SIZE);
}


void Gallery::keyPressed(int key){
	moveThumbnail(key);
}

void Gallery::swapThumbnails(int t1, int t2){
	ofVideoPlayer auxMov = movies[t2];
	movies[t2] = movies[t1];
	movies[t1] = auxMov;
	ofImage auxImg = thumbnailsImg[t2];
	thumbnailsImg[t2] = thumbnailsImg[t1];
	thumbnailsImg[t1] = auxImg;
	thumbnailSelected=t2;
}
void Gallery::moveThumbnail(int key){
	if(thumbnailSelected!=-1){
		if(key==OF_KEY_LEFT){
			if(thumbnailSelected > 0)
				swapThumbnails(thumbnailSelected, thumbnailSelected-1);
		}
		else if(key==OF_KEY_RIGHT){
			if(thumbnailSelected < numberOfMovies-1)
				swapThumbnails(thumbnailSelected, thumbnailSelected+1);
		}
		else if(key==OF_KEY_UP){
			if(thumbnailSelected > items-1)
				swapThumbnails(thumbnailSelected, thumbnailSelected-items);
		}
		else if(key==OF_KEY_DOWN){
			if(thumbnailSelected < numberOfMovies-items-1)
				swapThumbnails(thumbnailSelected, thumbnailSelected+items);
		}
	}
}
void Gallery::keyReleased(int key){}
void Gallery::mouseMoved(int x, int y){}
void Gallery::mouseDragged(int x, int y, int button){}
bool Gallery::movieWasPressed(int x, int y, int button){
	if(x<500){
		int line = (y/totalSize);
		int index = (x/totalSize)+line*items;
		int column = index%items;
		int xInMargin = ((column+1)*totalSize)-SIZE;
		int yInMargin = ((line+1)*totalSize)-SIZE;
		if(x >= xInMargin && y >= yInMargin)
			return true;
	}
	return false;
}
string Gallery::mousePressed(int x, int y, int button){
	ofVideoPlayer movie;
	int line = (y/totalSize);
	int index = getIndexMoviePressed(x, y);
	int column = index%items;
	int xInMargin = ((column+1)*totalSize)-SIZE;
	int yInMargin = ((line+1)*totalSize)-SIZE;
	if(x >= xInMargin && y >= yInMargin){
		movie= movies[index];
		thumbnailSelected = index;
		if(index < dir.size()){
			if(button == 2){
				movies[index].stop();
			} else if(movies[index].isPaused()){
					movies[index].setPaused(false);
					movies[index].play();
			} else movies[index].setPaused(true);
		}
	}
	string movieURL = movie.getMoviePath();
	return movieURL;
	
}
ofVideoPlayer Gallery::getVideoLoaded(){
	return movies[thumbnailSelected];
}

int Gallery::getIndexMoviePressed(int x, int y){
	int line = (y/totalSize);
	return (x/totalSize)+line*items;
}

void Gallery::scroll(){}
void Gallery::mouseReleased(int x, int y, int button){}
void Gallery::windowResized(int w, int h){}
void Gallery::gotMessage(ofMessage msg){}
void Gallery::dragEvent(ofDragInfo dragInfo){}
