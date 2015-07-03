#include "WebcamCapture.h"

WebcamCapture::WebcamCapture()
{
    if (cap.open(0)) {
        cap.set(CV_CAP_PROP_FRAME_WIDTH,800);
        cap.set(CV_CAP_PROP_FRAME_HEIGHT,600);
    }else{
        exit(2);
    }
}

WebcamCapture::~WebcamCapture()
{
    if(cap.isOpened()){
        cap.release();
    }
}

void WebcamCapture::run(){
    while (true) {
        cv::Mat rawImg;
        cap >> rawImg;
        cv::cvtColor(rawImg,rawImg,cv::COLOR_BGR2RGB);
        matVector.push_back(rawImg);
        emit newImageCaptured(matVector.size());
    }
}

int WebcamCapture::size(){
    return matVector.size();
}

cv::Mat WebcamCapture::getImageByIndex(int index){
    return matVector.at(index);
}
