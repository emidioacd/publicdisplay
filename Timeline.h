#pragma once

#include "ofMain.h"
#include "MyButton.h"
#define MARGIN 40
#define SIZE 500
class Timeline {
public:
	Timeline(void){}
	~Timeline(void){}
	
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void setMovie(ofVideoPlayer movie);
	void mousePressed(int x, int y, int button);
private:
	//MyButton previewBtn;
	ofVideoPlayer movie;
	//void drawButton(int x, int y, string label);
	void setFullScreen();
};
