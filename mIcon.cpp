#include "mIcon.h"


    void mIcon::setup(int x0, int y0, int w, int h, ofVideoPlayer m){
        cout << "loading movie: "<< url<<endl;

        x = x0;
        y = y0;
        width = w;
        height = h;
        movie = m;
        currentFrame = 0;
        wait = 0;
        totalFrames = m.getTotalNumFrames();


		/*image.allocate(width, height, OF_IMAGE_COLOR);
        ofImage img = ofImage();
        img.setFromPixels(m.getPixelsRef());
        frames[0] = img;*/
    }


	void mIcon::update(){
	    int jump = totalFrames/10;
        wait++;
        if(wait == 20){
            currentFrame+=jump;
            currentFrame = currentFrame%totalFrames;

            wait = 0;
        }

	}

	void mIcon::draw(){
	    movie.setFrame(currentFrame);
        movie.draw(x, y, width, height);

    }

	int mIcon::getX(){
		return x;
	}
	int mIcon::getY(){
		return y;
	}
	ofImage mIcon::getImage(){
		return image;
	}
	string mIcon::getUrl(){
		return url;
	}
	int mIcon::getFirstFrame(){
		return firstFrame;
	}
	int mIcon::getWidth(){
		return width;
	}
	int mIcon::getHeight(){
		return height;
	}
	void mIcon::setX(int value){
		x=value;
	}
	void mIcon::setY(int value){
		y=value;
	}
	void mIcon::setWidth(int value){
		width=value;
	}
	void mIcon::setHeight(int value){
		height=value;
	}
	void mIcon::setImage(ofImage value){
		image=value;
	}
	void mIcon::setUrl(string url){
		this->url = url;
	}
	void mIcon::setFirstFrame(int frame){
		this->firstFrame = frame;
	}
	bool mIcon::isOnImage(int valX, int valY){
		return(x < valX && valX < x+width && y < valY && valY < y+height);
	}

