#include "mIcon.h"

mIcon::mIcon(void){
	image = ofImage();
	firstFrame=0;
}
mIcon::~mIcon(void){}

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

