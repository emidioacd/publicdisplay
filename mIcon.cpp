#include "mIcon.h"

mIcon::mIcon(void){
	image = ofImage();}
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
	bool mIcon::isOnImage(int valX, int valY){	
		return(x < valX < x+width && y < valY < y+width);
	}

