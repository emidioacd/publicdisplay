#include "gallery.h"

void Gallery::setup(int galleryWidth){
	thumbnailSelected=-1;
	width= galleryWidth;
	items = width/(SIZE_G + MARGINBETWEENTHUMBNAIL);
	totalSize = SIZE_G + MARGIN;
	dir.listDir("movies");
	dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order
	ofSetVerticalSync(true);
	if( dir.size() ){
		movies.assign(dir.size(), ofVideoPlayer());
		thumbnailsImg.assign(dir.size(), mIcon());
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
		if(dir.size() == 0){
			ofSetColor(ofColor::gray);
			string no_videos = "No videos!";
			ofDrawBitmapString(no_videos, ofGetWidth()/2 , ofGetHeight()/2);
		}
		int hmargin = MARGIN;
		int wmargin = MARGIN;
		
		for(int i = 0; i < numberOfMovies; i++){
			if(i!= 0 && i%items == 0){
				hmargin+=SIZE_G + MARGINBETWEENTHUMBNAIL;
				wmargin = MARGIN;
			}else 
				if(i!=0) 
					wmargin+=SIZE_G + MARGINBETWEENTHUMBNAIL;
			ofSetColor(ofColor::white);

			if(thumbnailSelected==i)
				ofSetColor(ofColor::blue);

			drawFrame(wmargin, hmargin, i, movies[i]);
			//movies[i].draw(wmargin, hmargin, SIZE_G, SIZE_G);
		}
		first=false;
	//}
}
void Gallery::drawFrame(int x, int y, int index, ofVideoPlayer movie){
	if(first){
		thumbnailsImg[index].getImage().allocate(SIZE_G, SIZE_G, OF_IMAGE_COLOR);
		ofImage img = ofImage();
		img.setFromPixels(movie.getPixelsRef());
		thumbnailsImg[index].setImage(img);
		thumbnailsImg[index].setX(x);
		thumbnailsImg[index].setY(y);
		thumbnailsImg[index].setWidth(SIZE_G);
		thumbnailsImg[index].setHeight(y);
	}
	thumbnailsImg[index].getImage().draw(x, y, SIZE_G, SIZE_G);
}

void Gallery::keyPressed(int key){
	moveThumbnail(key);
}

void Gallery::swapThumbnails(int t1, int t2){
	ofVideoPlayer auxMov = movies[t2];
	movies[t2] = movies[t1];
	movies[t1] = auxMov;
	ofImage auxImg = thumbnailsImg[t2].getImage();
	thumbnailsImg[t2].setImage(thumbnailsImg[t1].getImage());
	thumbnailsImg[t1].setImage(auxImg);
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
			if(thumbnailSelected < numberOfMovies-items)
				swapThumbnails(thumbnailSelected, thumbnailSelected+items);
		}
	}
}
void Gallery::keyReleased(int key){}
void Gallery::mouseMoved(int x, int y){}
void Gallery::mouseDragged(int x, int y, int button){}

string Gallery::mousePressed(int x, int y, int button){
	ofVideoPlayer movie;
	int line = (y/totalSize);
	int index = getIndexMoviePressed(x, y);
	int column = index%items;

	//Percorre a todas as thumbnails ate' 'a que foi selecionada
	for(int i = 0; i < thumbnailsImg.size(); i++){
		if(thumbnailsImg[i].isOnImage(x, y)){
			movie= movies[index];
		thumbnailSelected = index;
		if(index < dir.size()){
			if(button == 2){
				movies[index].stop();
			} else 
				if(movies[index].isPaused()){
					movies[index].setPaused(false);
					movies[index].play();
			} else 
				movies[index].setPaused(true);
		}
		}

	}

	/*int xInMargin = ((column+1)*totalSize)-SIZE;
	int yInMargin = ((line+1)*totalSize)-SIZE;
	if(x >= xInMargin && y >= yInMargin){
		movie= movies[index];
		thumbnailSelected = index;
		if(index < dir.size()){
			if(button == 2){
				movies[index].stop();
			} else 
				if(movies[index].isPaused()){
					movies[index].setPaused(false);
					movies[index].play();
			} else 
				movies[index].setPaused(true);
		}
	}*/
	string movieURL = movie.getMoviePath();
	return movieURL;
	
}

int Gallery::getIndexMoviePressed(int x, int y){
	int line = (y/totalSize);
	return (x/totalSize)+line*items;
}
ofVideoPlayer Gallery::getVideoLoaded(){
	return movies[thumbnailSelected];
}

void Gallery::scroll(){}
void Gallery::mouseReleased(int x, int y, int button){}
void Gallery::windowResized(int w, int h){}
void Gallery::gotMessage(ofMessage msg){}
void Gallery::dragEvent(ofDragInfo dragInfo){}
