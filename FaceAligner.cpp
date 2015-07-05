#include "FaceAligner.h"

FaceAligner::FaceAligner():initial_number(20),landmarkNum(114)
{
    regressor = ShapeRegressor();
    regressor.load("/home/netbeen/workspace/20141015-ESR-HelenDatabase/data/model-Helen114-HaarAlt2-10-120.txt");
}

FaceAligner::~FaceAligner()
{

}


void FaceAligner::doAlignment(){
    currentShape =  regressor.predict(this->grayImg, this->boundingBox, this->initial_number);
    emit this->alignmentCompete();
    return;
}

cv::Mat_<double> FaceAligner::getCurrentShape(){
    return currentShape;
}

void FaceAligner::setNextFrame(cv::Mat &grayImg, BoundingBox &boundingBox){
    this->grayImg = grayImg;
    this->boundingBox = boundingBox;
}
