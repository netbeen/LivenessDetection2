#include "FaceAligner.h"

FaceAligner::FaceAligner():initial_number(20),landmarkNum(114),receiveNewData(false)
{
    regressor = ShapeRegressor();
    regressor.load("/home/netbeen/workspace/20141015-ESR-HelenDatabase/data/model-Helen114-HaarAlt2-10-120.txt");
}

FaceAligner::~FaceAligner()
{

}


void FaceAligner::doAlignment(){
    //this->grayImg = grayImg;
    //this->boundingBox = boundingBox;
    //receiveNewData = true;
    currentShape =  regressor.predict(grayImg, boundingBox, this->initial_number);
    emit this->alignmentCompete();
    return;
}

/*void FaceAligner::run(){
    while(true){
        if(receiveNewData){
            currentShape =  regressor.predict(grayImg, boundingBox, this->initial_number);
            receiveNewData = false;
            emit this->alignmentCompete();
        }
    }
}*/

cv::Mat_<double> FaceAligner::getCurrentShape(){
    return currentShape;
}

void FaceAligner::setNextFrame(cv::Mat &grayImg, BoundingBox &boundingBox){
    this->grayImg = grayImg;
    this->boundingBox = boundingBox;
}
