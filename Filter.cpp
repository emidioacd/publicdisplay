
#include "Filter.h"


void Filter::setup(int x, int y, int h, int w, int ph, int pw, ofVideoPlayer m){
    movieHeight = h;
    movieWidth = w;
    playerWidth = pw;
    playerHeight = ph;
    posX = x;
    posY = y;
    movie = m;
    videoTexture.allocate(movieWidth,movieHeight, GL_RGB);
    videoFilter	= new unsigned char[movieWidth*movieHeight*3];


}
void Filter::update(){
    //sharperFilter();
    //blurFilter();
    //bwFilter();
    //greyFilter();
    edgesFilter();
}

void Filter::draw(){
    videoTexture.draw(posX,posY,playerWidth,playerHeight);
}

void Filter::negativeFilter(){
    if (movie.isFrameNew()){
        int totalPixels = movieWidth*movieHeight*3;
        unsigned char * pixels = movie.getPixels();
        for (int i = 0; i < totalPixels; i++){
            videoFilter[i] = 255 - pixels[i];
        }
        videoTexture.loadData(videoFilter, movieWidth,movieHeight, GL_RGB);
    }
}

void Filter::sharperFilter(){
    int totalPixels = movieWidth*movieHeight*3;
    pixels = movie.getPixels();

    for (int w = 0; w < (movieWidth-2); w++){
        for (int h = 0; h < (movieHeight-2); h++){

            int resultR = 0;
            int resultG = 0;
            int resultB = 0;
            int index = ((h+1)*(movieWidth)+w+1)*3;

            for(int mw = 0; mw < 3; mw++){
                for(int mh = 0; mh < 3; mh++){
                    int aux = ((h+mh)*(movieWidth)+mw+w)*3;

                    resultR += sharperMatrix[mw][mh]*pixels[aux];
                    resultG += sharperMatrix[mw][mh]*pixels[aux+1];
                    resultB += sharperMatrix[mw][mh]*pixels[aux+2];
                }
            }
            videoFilter[index] =  truncColor(resultR);
            videoFilter[index+1] = truncColor(resultG);
            videoFilter[index+2] =   truncColor(resultB);
        }
    }
    videoTexture.loadData(videoFilter, movieWidth,movieHeight, GL_RGB);
}



void Filter::blurFilter(){
    int totalPixels = movieWidth*movieHeight*3;
    pixels = movie.getPixels();

    for (int w = 0; w < (movieWidth-4); w++){
        for (int h = 0; h < (movieHeight-4); h++){

            int resultR = 0;
            int resultG = 0;
            int resultB = 0;

            int index = ((h+1)*(movieWidth)+w+1)*3;


            for(int mw = 0; mw < 5; mw++){
                for(int mh = 0; mh < 5; mh++){
                    int aux = ((h+mh)*(movieWidth)+mw+w)*3;

                    resultR += pixels[aux];
                    resultG += pixels[aux+1];
                    resultB += pixels[aux+2];
                }
            }
            videoFilter[index] =  truncColor(resultR/blurWeight);
            videoFilter[index+1] = truncColor(resultG/blurWeight);
            videoFilter[index+2] =   truncColor(resultB/blurWeight);
        }
    }
    videoTexture.loadData(videoFilter, movieWidth,movieHeight, GL_RGB);
}

void Filter::bwFilter(){
    int totalPixels = movieWidth*movieHeight*3;
    pixels = movie.getPixels();

    for (int w = 0; w < movieWidth; w++){
        for (int h = 0; h < movieHeight; h++){

            int index = ((h*movieWidth)+w)*3;

            int result = ((pixels[index]+pixels[index+1]+pixels[index+2])/3 > 128) ? 255 : 0;

            videoFilter[index] = result;
            videoFilter[index+1] = result ;
            videoFilter[index+2] = result;
        }
    }
    videoTexture.loadData(videoFilter, movieWidth,movieHeight, GL_RGB);
}

void Filter::greyFilter(){
    int totalPixels = movieWidth*movieHeight*3;
    double a = 0.21;
    double b = 0.71;
    double c = 0.07;

    pixels = movie.getPixels();

    for (int w = 0; w < movieWidth; w++){
        for (int h = 0; h < movieHeight; h++){

            int index = ((h*movieWidth)+w)*3;
            int result = a*pixels[index] + b*pixels[index+1] + c*pixels[index+2];

            videoFilter[index] =  result;
            videoFilter[index+1] = result;
            videoFilter[index+2] =   result;
        }
    }
    videoTexture.loadData(videoFilter, movieWidth,movieHeight, GL_RGB);
}

void Filter::edgesFilter(){
  int totalPixels = movieWidth*movieHeight*3;
    pixels = movie.getPixels();

    for (int w = 0; w < (movieWidth-2); w++){
        for (int h = 0; h < (movieHeight-2); h++){

            int resultR = 0;
            int resultG = 0;
            int resultB = 0;
            int index = ((h+1)*(movieWidth)+w+1)*3;

            for(int mw = 0; mw < 3; mw++){
                for(int mh = 0; mh < 3; mh++){
                    int aux = ((h+mh)*(movieWidth)+mw+w)*3;

                    resultR += edgesMatrix[mw][mh]*pixels[aux];
                    resultG += edgesMatrix[mw][mh]*pixels[aux+1];
                    resultB += edgesMatrix[mw][mh]*pixels[aux+2];
                }
            }

            videoFilter[index] =  (resultR > 255) ? 255 : (resultR < 0 ? 0: resultR);
            videoFilter[index+1] = (resultG > 255) ? 255 : (resultG < 0 ? 0: resultG);
            videoFilter[index+2] =  (resultB > 255) ? 255 : (resultB < 0 ? 0: resultB);
        }
    }
    videoTexture.loadData(videoFilter, movieWidth,movieHeight, GL_RGB);

}

int Filter::truncColor(int color)
{
    int res = color;
    if(color > 255) {
       res= 255;
    }else if(color < 0){
       res= 0;
    }

    return res;

}


void Filter::guiEvent(ofxUIEventArgs &e)
{

}

void Filter::keyPressed(int key){
}
void Filter::keyReleased(int key){}
void Filter::mouseMoved(int x, int y){}
void Filter::mouseDragged(int x, int y, int button){}
void Filter::mousePressed(int x, int y, int button){}

void Filter::mouseReleased(int x, int y, int button){}
void Filter::windowResized(int w, int h){}
void Filter::gotMessage(ofMessage msg){}
void Filter::dragEvent(ofDragInfo dragInfo){}
