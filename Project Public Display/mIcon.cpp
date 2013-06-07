#include "mIcon.h"


    void mIcon::setup(int x0, int y0, int w, int h, string path){
        cout << "loading movie for micon: "<< path<<endl;
        hover = false;
        x = x0;
        y = y0;
        width = w;
        height = h;
        url = path;
        movie = ofVideoPlayer();

        movie.loadMovie(path);
        movie.setVolume(0);

        currentFrame = 0;
        wait = 0;
        totalFrames = movie.getTotalNumFrames();

		/*image.allocate(width, height, OF_IMAGE_COLOR);
        ofImage img = ofImage();
        img.setFromPixels(m.getPixelsRef());
        frames[0] = img;*/
    }


	void mIcon::update(){
	    int jump = totalFrames/10;
        wait++;
        if(wait == 10){
            if(hover){
                currentFrame+=jump;
                currentFrame = currentFrame%totalFrames;
            }else currentFrame = 0;
            wait = 0;
        }
        movie.update();

	}

	void mIcon::draw()
	{
	    movie.setFrame(currentFrame);

        movie.draw(x, y, width, height);


    }
    void mIcon::mouseMoved(int mouseX, int mouseY){

        if((mouseX>x && mouseX<x+width) && (mouseY>y && mouseY<y+height)){
            hover = true;

        }else hover = false;

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
        movie = ofVideoPlayer();
        movie.loadMovie(url);
	}
	void mIcon::setFirstFrame(int frame){
		this->firstFrame = frame;
	}
	bool mIcon::isOnImage(int valX, int valY){
		return(x < valX && valX < x+width && y < valY && valY < y+height);
	}

