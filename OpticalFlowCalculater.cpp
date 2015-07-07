#include "OpticalFlowCalculater.h"

OpticalFlowCalculater::OpticalFlowCalculater():preFrameVaild(false)
{
    this->norm.create(600,800, CV_32FC1);
    this->phaseAngle.create(600,800, CV_8UC1);
}

OpticalFlowCalculater::~OpticalFlowCalculater()
{

}

void OpticalFlowCalculater::calc(){
    if(this->preFrameVaild == false){
        this->preFrame = this->currentFrame;
    }
    calcOpticalFlowFarneback(this->preFrame, this->currentFrame, this->opticalFlow, 0.1, 1, 50, 3, 7, 1.5, 0);
    this->separateNromAndAngle(this->opticalFlow, this->norm,this->phaseAngle);
    emit this->calcCompete();
}

void OpticalFlowCalculater::receiveNewFrame(cv::Mat& newFrame){
    if(this->currentFrame.data == nullptr){
        this->currentFrame = newFrame;
    }else{
        this->preFrame = this->currentFrame;
        this->preFrameVaild = true;
        this->currentFrame = newFrame;
    }
}

void OpticalFlowCalculater::separateNromAndAngle(const cv::Mat& flow, cv::Mat& norm, cv::Mat& phaseAngle){
    for(int rowIndex = 0; rowIndex<flow.rows; ++rowIndex){
        for(int columnIndex = 0; columnIndex<flow.cols; ++columnIndex){
            cv::Vec2f flow_at_point = flow.at<cv::Vec2f>(rowIndex, columnIndex);
            float normValue = std::sqrt(std::pow(flow_at_point[0],2)+std::pow(flow_at_point[1],2));
            norm.at<float>(rowIndex, columnIndex)=normValue;
            float angleValue = atan2(flow_at_point[0],flow_at_point[1]);
            uchar angleValueUchar = static_cast<uchar>(((angleValue/3.1415926*180)/180*127)+127);		//将float的-pi到pi的值映射到0-255的uchar来显示
            phaseAngle.at<uchar>(rowIndex, columnIndex)=angleValueUchar;
        }
    }
}

cv::Mat OpticalFlowCalculater::getNrom(){
    return this->norm;
}

cv::Mat OpticalFlowCalculater::getPhaseAngle(){
    return this->phaseAngle;
}
