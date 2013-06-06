#include "gallery.h"

void Gallery::setup(int galleryWidth){
	thumbnailSelected=-1;
	width= galleryWidth;
	items = width/(SIZE_G + MARGINBETWEENTHUMBNAIL);
	totalSize = SIZE_G + MARGIN_G;

	//if(!loadGallery()){
		dir.listDir("movies");
		dir.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order
		ofSetVerticalSync(true);
		if( dir.size() ){
			movies.assign(dir.size(), ofVideoPlayer());
			thumbnailsImg.assign(dir.size(), mIcon());
		}
		numberOfMovies = dir.size();
		for(int i = 0 ; i < numberOfMovies ; i++){
			string path = dir.getPath(i);
			movies[i].loadMovie(path);
			cout<<"path: "<<dir.getPath(i)<<endl;
			thumbnailsImg[i].setUrl(path);

			//TODO so para teste
			if(i!=0)
				thumbnailsImg[i].setFirstFrame(50);
			}
	//}
	ofBackground(ofColor::white);
	first=true;
}
void Gallery::update(){
	for(int i = 0; i < (int)dir.size(); i++){
		movies[i].update();
	}
}

void Gallery::draw(){
	if(numberOfMovies == 0){
		ofSetColor(ofColor::gray);
		string no_videos = "No videos!";
		ofDrawBitmapString(no_videos, ofGetWidth()/2 , ofGetHeight()/2);
	}
	int hmargin = MARGIN_G;
	int wmargin = MARGIN_G;

	for(int i = 0 ; i < numberOfMovies ; i++){
		if(first){
			if(i != 0 && i%items == 0){
				hmargin += SIZE_G + MARGINBETWEENTHUMBNAIL;
				wmargin = MARGIN_G;
			}else
				if(i!=0)
					wmargin += SIZE_G + MARGINBETWEENTHUMBNAIL;
		}
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
		cout << "loading movie"<<endl;
		thumbnailsImg[index].getImage().allocate(SIZE_G, SIZE_G, OF_IMAGE_COLOR);
		ofImage img = ofImage();
		img.setFromPixels(movie.getPixelsRef());

		thumbnailsImg[index].setImage(img);
		thumbnailsImg[index].setX(x);
		thumbnailsImg[index].setY(y);
		thumbnailsImg[index].setWidth(SIZE_G);
		thumbnailsImg[index].setHeight(SIZE_G);
		thumbnailsImg[index].getImage().draw(x, y, SIZE_G, SIZE_G);
	}else{
		thumbnailsImg[index].getImage().draw(thumbnailsImg[index].getX(), thumbnailsImg[index].getY(), thumbnailsImg[index].getWidth(), thumbnailsImg[index].getHeight());
	}

}

void Gallery::keyPressed(int key){
	moveThumbnail(key);
}

void Gallery::swapThumbnails(int t1, int t2){
	ofVideoPlayer auxMov = movies[t2];
	movies[t2] = movies[t1];
	movies[t1] = auxMov;
	ofImage auxImg = thumbnailsImg[t1].getImage();
	string auxUrl = thumbnailsImg[t1].getUrl();
	thumbnailsImg[t1].setImage(thumbnailsImg[t2].getImage());
	thumbnailsImg[t1].setUrl(thumbnailsImg[t2].getUrl());
	thumbnailsImg[t2].setImage(auxImg);
	thumbnailsImg[t2].setUrl(auxUrl);
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
	string movieURL = "";
	ofVideoPlayer movie;
	//Percorre a todas as thumbnails ate' 'a que foi selecionada
	for(int i = 0; i < thumbnailsImg.size(); i++)
	{
		if(thumbnailsImg[i].isOnImage(x, y))
		{
			movie = movies[i];

			thumbnailSelected = i;
			if(button == 2)
			{
				movies[i].stop();
			} else
			{
				if(movies[i].isPaused())
				{
					movies[i].setPaused(false);
					movies[i].play();
				} else
					movies[i].setPaused(true);
			}
		movieURL = movie.getMoviePath();
		break;
		}

	}
	if(movieURL=="")
		thumbnailSelected = -1;
	return movieURL;
}

int Gallery::getIndexMoviePressed(int x, int y){
	int line = (y/totalSize);
	return (x/totalSize)+line*items;
}
ofVideoPlayer Gallery::getVideoLoaded(){
	return movies[thumbnailSelected];
}
/** guarda num ficheiro de XML os parametros dos videos
	e' chamado no testApp.exit()
*/
void Gallery::saveGallery(){
	ofxXmlSettings settings;
	//cria um no' para os videos
	settings.addTag("videos");
	settings.pushTag("videos");

	//cria um no' para cada um dos videos e para cada uma das caracteristicas
	//<videos><video><url>xpto/movie.mov</url><firstFrame>20</firstFrame></video></videos>
	for(int i = 0; i < thumbnailsImg.size() ; i++){
		mIcon mIcon = thumbnailsImg[i];

		//adiciona o no' video
		settings.addTag("video");
		settings.pushTag("video",i);

		//adiciona os parametros do no' video
		settings.addValue("url", mIcon.getUrl());
		settings.addValue("firstFrame", toString(mIcon.getFirstFrame()));

		//conclui a edicao do no video
		settings.popTag();
	}
	//conclui a edicao do no videos
	settings.popTag();
	settings.saveFile(xmlFile);
}

//guarda estado da galeria (ordem de apresentacao, frame de inicio, TODO)
bool Gallery::loadGallery(){
	ofxXmlSettings settings;
	bool hasFile = settings.loadFile(xmlFile);
	if(hasFile)
	{
		settings.pushTag("videos");

		int numTags = settings.getNumTags("video");
		numberOfMovies = numTags;
		movies.assign(numTags, ofVideoPlayer());
		thumbnailsImg.assign(numTags, mIcon());
		cout << "numTags: " << numTags << endl;

		for(int i = 0 ; i<numTags ; i++)
		{
			settings.pushTag("video", i);
			string url = settings.getValue("url", "");
			thumbnailsImg[i].setFirstFrame(settings.getValue("firstFrame", 0));
			cout << "url: " << url << endl;
			movies[i].loadMovie(url);
			thumbnailsImg[i].setUrl(url);
			settings.popTag();
		}
			settings.popTag();
	}
	return hasFile;
}
string Gallery::toString(int value){
	ostringstream convert;
	convert<<value;
	return convert.str();
}

void Gallery::scroll(){}
void Gallery::mouseReleased(int x, int y, int button){}
void Gallery::windowResized(int w, int h){}
void Gallery::gotMessage(ofMessage msg){}
void Gallery::dragEvent(ofDragInfo dragInfo){}
