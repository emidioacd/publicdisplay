#include "Movie.h"

void Movie::setup(ofVideoPlayer movieA, int numFilters, int firstFrameA, int lastFrameA){
    movie = movieA;
    firstFrame = firstFrameA;
    lastFrame = lastFrameA;
    filters.assign(numFilters,Filter());

   playerWidth = 320;
   playerHeight = 240;

    h = movie.getHeight();
    w = movie.getWidth();

}


void Movie::update(){
    if(movie.getCurrentFrame() >= lastFrame-3){
       movie.stop();
    }else{
        movie.update();
        for(int i = 0; i< filters.size(); i++)
            filters[i].update();
    }
}

//--------------------------------------------------------------
void Movie::draw(){
    movie.draw(posX, posY, playerWidth, playerHeight);

    for(int i = 0; i< filters.size(); i++)
        filters[i].draw();
}

void Movie::pause(bool p){
    movie.setPaused(p);
}

void Movie::play(){

    for(int i = 0; i< filters.size(); i++)
        filters[i].setup();

    movie.setFrame(firstFrame);
    movie.play();
}
void Movie::stop(){

    movie.stop();
}

bool Movie::stopped(){
    return !movie.isPlaying();
}

int Movie::getHeight(){
    return movie.getHeight();
}

int Movie::getWidth(){
    return movie.getWidth();
}

void Movie::addFilter(int index,string filterName,int ff, int lf){
    // Nao pode fazer já o setup, inicializa apenas as variaveis,
    // pois todo o vector de filtros deve estar preenchido para ser feito o setup de cada filtro
   filters[index].setVariables(posX, posY, h, w, playerHeight, playerWidth, filterName, ff, lf, movie);

}


//--------------------------------------------------------------
void Movie::keyPressed(int key){}
void Movie::keyReleased(int key){}
void Movie::mouseMoved(int x, int y){}
void Movie::mouseDragged(int x, int y, int button){}
void Movie::mousePressed(int x, int y, int button){}

void Movie::mouseReleased(int x, int y, int button){}
void Movie::windowResized(int w, int h){}
void Movie::gotMessage(ofMessage msg){}
void Movie::dragEvent(ofDragInfo dragInfo){}





