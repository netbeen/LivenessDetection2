#include "ProgressController.h"

ProgressController* ProgressController::ptr2ProgressController = nullptr;

ProgressController::ProgressController():sliderOnewayTime(3000),horizontalSliderPercentage(49),horizontalSliderIsGoingLeft(true),edgeSleepTime(2000)
{
    updateSliderTimer = new QTimer(this);
    QObject::connect(updateSliderTimer,SIGNAL(timeout()),this,SLOT(changeHorizontalSliderPercentage()));

    edgeSleepTimer = new QTimer(this);
    QObject::connect(edgeSleepTimer,SIGNAL(timeout()),this,SLOT(changeHorizontalSliderOrientation()));

}

ProgressController::~ProgressController()
{

}

void ProgressController::startProgress(){
    updateSliderTimer->start( this->sliderOnewayTime/50 );
}

ProgressController* ProgressController::getInstance(){
    if(ProgressController::ptr2ProgressController == nullptr){
        ptr2ProgressController = new ProgressController();
    }
    return ptr2ProgressController;
}

void ProgressController::changeHorizontalSliderPercentage(){
    if(this->horizontalSliderIsGoingLeft == true){
        this->horizontalSliderPercentage--;
    }else{
        this->horizontalSliderPercentage++;
    }
    emit updateHorizontalSlider(horizontalSliderPercentage);
    if(horizontalSliderPercentage == 0 || horizontalSliderPercentage == 97){
        this->updateSliderTimer->stop();
        this->edgeSleepTimer->start(edgeSleepTime);
    }
}

void ProgressController::changeHorizontalSliderOrientation(){
    this->edgeSleepTimer->stop();
    this->horizontalSliderIsGoingLeft = (this->horizontalSliderIsGoingLeft==true)?false:true;
    this->updateSliderTimer->start(this->sliderOnewayTime/50);
}
