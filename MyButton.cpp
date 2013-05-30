#include "MyButton.h"


void MyButton::setup(){
	//preview = new Button(20, 20, "Preview");
}

void MyButton::update(){
}
void MyButton::draw(){
	ofDrawBitmapString("", 20, 20);
}
bool MyButton::wasPressed(int pressedX, int pressedY){
	return (pressedX > x && pressedX < x + width && pressedY < y && pressedY > y - height);
}

