#pragma once

#include "ofMain.h"
class MyButton {
public:
	MyButton(int paramX, int paramY, int paramHeight, int paramWidth, string paramLabel){x=paramX;};
	~MyButton(void){};
	
	void draw();
	void setup();
	void update();

	bool wasPressed(int x, int y);
private:
	int x;
	int y;
	int width;
	int height;
	int label;
};
