#include "ProgressController.h"

ProgressController* ProgressController::ptr2ProgressController = nullptr;

ProgressController::ProgressController():sliderOnewayTime(1500),horizontalSliderPercentage(49),horizontalSliderIsGoingLeft(true),edgeSleepTime(1500)
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
    if(horizontalSliderPercentage == 0 || horizontalSliderPercentage == 97){        //由于滑块的宽度为2,所以不能顶到99，那样会造成视觉上的不美观。
        this->updateSliderTimer->stop();
        this->edgeSleepTimer->start(edgeSleepTime);     // 开启睡眠计时器
    }
}

//private slot,用于改变滑块方向，并重启滑块的滑动
void ProgressController::changeHorizontalSliderOrientation(){
    this->edgeSleepTimer->stop();
    this->horizontalSliderIsGoingLeft = (this->horizontalSliderIsGoingLeft==true)?false:true;
    this->updateSliderTimer->start(this->sliderOnewayTime/50);
}
