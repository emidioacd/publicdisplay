
#include "MovieTimeline.h"

void MovieTimeline::setup(ofVideoPlayer movieA, int numFilters, int firstFrameA, int lastFrameA){
    movie = movieA;
    firstFrame = firstFrameA;
    lastFrame = lastFrameA;
    filters.assign(numFilters,Filter());

   playerWidth = 320;
   playerHeight = 240;

    h = movie.getHeight();
    w = movie.getWidth();

}


void MovieTimeline::update(){
    if(movie.getCurrentFrame() >= lastFrame-3){
       movie.stop();
    }else{
        movie.update();
        for(int i = 0; i< filters.size(); i++)
            filters[i].update();
    }
}

//--------------------------------------------------------------
void MovieTimeline::draw(){
    movie.draw(posX, posY, playerWidth, playerHeight);

    for(int i = 0; i< filters.size(); i++)
        filters[i].draw();
}

void MovieTimeline::pause(bool p){
    movie.setPaused(p);
}

void MovieTimeline::play(){

    for(int i = 0; i< filters.size(); i++)
        filters[i].setup();

    movie.setFrame(firstFrame);
    movie.play();
}
void MovieTimeline::stop(){

    movie.stop();
}

bool MovieTimeline::stopped(){
    return !movie.isPlaying();
}

int MovieTimeline::getHeight(){
    return movie.getHeight();
}

int MovieTimeline::getWidth(){
    return movie.getWidth();
}

void MovieTimeline::addFilter(int index,string filterName,int ff, int lf){
    // Nao pode fazer já o setup, inicializa apenas as variaveis,
    // pois todo o vector de filtros deve estar preenchido para ser feito o setup de cada filtro
   filters[index].setVariables(posX, posY, h, w, playerHeight, playerWidth, filterName, ff, lf, movie);

}


//--------------------------------------------------------------
void MovieTimeline::keyPressed(int key){}
void MovieTimeline::keyReleased(int key){}
void MovieTimeline::mouseMoved(int x, int y){}
void MovieTimeline::mouseDragged(int x, int y, int button){}
void MovieTimeline::mousePressed(int x, int y, int button){}

void MovieTimeline::mouseReleased(int x, int y, int button){}
void MovieTimeline::windowResized(int w, int h){}
void MovieTimeline::gotMessage(ofMessage msg){}
void MovieTimeline::dragEvent(ofDragInfo dragInfo){}




