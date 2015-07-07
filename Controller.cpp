#include "Controller.h"

//单例模式的静态指针的定义+初始化
Controller* Controller::ptr2Controller = nullptr;

Controller::Controller():isShapeValid(false),isAligning(false),mainFrameRate(0),faceAlignmentFrameRate(0),isOpticalFlowCalculateing(false),opticalFlowFrameRate(0)
{
    webcamCapture = new WebcamCapture();

    QObject::connect(webcamCapture,SIGNAL(newImageCaptured(int)),this,SLOT(receiveNewImage(int)));


    faceDetector = new FaceDetector();
    eyeDetector = new EyeDetector();
    faceAligner = new FaceAligner();
    opticalFlowCalculater = new OpticalFlowCalculater();

    progressController = ProgressController::getInstance();
    progressControllerThread = new QThread();
    progressController->moveToThread(progressControllerThread);

    faceAlignerThread = new QThread;
    faceAligner->moveToThread(faceAlignerThread);

    QObject::connect(this, SIGNAL(doAlignment()), faceAligner, SLOT(doAlignment()) );
    QObject::connect( faceAligner,SIGNAL(alignmentCompete()) , this, SLOT(receiveShape())  );

    opticalFlowCalculaterThread = new QThread();
    opticalFlowCalculater->moveToThread(opticalFlowCalculaterThread);

    QObject::connect(this,SIGNAL(calcOpticalFlow()),opticalFlowCalculater,SLOT(calc()));
    QObject::connect(opticalFlowCalculater,SIGNAL(calcCompete()),this,SLOT(receiveOpticalFlow()));

}

Controller::~Controller()
{
    delete webcamCapture;
}

//一个slot，当控制器收到WebcamCapture的信号的时候，做出的响应。
void Controller::receiveNewImage(int index){
    rawImage = webcamCapture->getImageByIndex(index-1);
    cv::cvtColor(this->rawImage,this->grayImage,cv::COLOR_RGB2GRAY);

    if (faceDetector->detect(this->grayImage,5, this->boundingBox)) {       //调用FaceDetector
        this->drawRect(rawImage,boundingBox);
        this->upperImage =  grayImage(boundingBox.returnUpperRect());       //调用EyeDector
        if(eyeDetector->detect(this->upperImage,this->eyesRects)){
            this->drawRect(rawImage, eyesRects);
        }

        if(isShapeValid == false && isAligning == false){       //初始状态，形状无效，未在对齐
            this->isAligning = true;
            faceAligner->setNextFrame(grayImage, boundingBox);
            emit this->doAlignment();
        }else if(isShapeValid == false && isAligning == true){      // 形状无效，正在对齐
            ;
        }else if(isShapeValid == true && isAligning == false){      //形状有效，未在对齐
            faceAligner->setNextFrame(grayImage, boundingBox);
            emit this->doAlignment();
            this->drawPoint(rawImage,shape);
            this->isAligning = true;
        }else{      //形状有效，正在对齐。
            this->drawPoint(rawImage,shape);
        }

    }
    emit controllerReceivesNewImage();
    mainFrameRate++;
}

void Controller::drawRect(cv::Mat& input, BoundingBox& boundingBox){
    cv::rectangle(input, boundingBox.returnRect(), cv::Scalar(0, 255, 255), 3, 8, 0);
    return;
}

void Controller::drawRect(cv::Mat &input, std::vector<cv::Rect>& eyesRects){
    for(cv::Rect& rectElem : eyesRects){
        rectElem.x +=boundingBox.returnRect().x;        //加上人脸框X轴的偏移
        rectElem.y +=boundingBox.returnRect().y;        //加上人脸框Y轴的偏移
        cv::rectangle(input, rectElem, cv::Scalar(0, 255, 255), 3, 8, 0);
    }
}

Controller* Controller::getInstance(){
    if(Controller::ptr2Controller == nullptr){
        Controller::ptr2Controller = new Controller();
    }
    return Controller::ptr2Controller;
}

cv::Mat Controller::getRawImage(){
    return rawImage;
}


void Controller::drawPoint(cv::Mat& input, cv::Mat_<double>& shape){
    for (int i = 0; i < shape.rows; i++) {
        circle(input, cv::Point2d(shape(i, 0), shape(i, 1)), 3, cv::Scalar(0, 255, 0), -1, 8, 0);
    }
}

//一个slot，在收到“配准完毕”信号之后的动作：更新配准形状，并进行光流计算
void Controller::receiveShape(){
    this->shape = faceAligner->getCurrentShape();
    this->isShapeValid=true;
    this->isAligning = false;
    faceAlignmentFrameRate++;

    if(this->isOpticalFlowCalculateing == false){
        this->isOpticalFlowCalculateing = true;
        opticalFlowCalculater->receiveNewFrame(grayImage);
        emit this->calcOpticalFlow();
    }
    return;
}

int Controller::getMainFrameRate(){
    int count = this->mainFrameRate;
    mainFrameRate = 0;
    return count;
}

int Controller::getFaceAlignmentFrameRate(){
    int count = this->faceAlignmentFrameRate;
    faceAlignmentFrameRate = 0;
    return count;
}

int Controller::getOpticalFlowFrameRate(){
    int count = this->opticalFlowFrameRate;
    opticalFlowFrameRate = 0;
    return count;
}


void Controller::startToRun(){
    webcamCapture->start();
    faceAlignerThread->start();
    progressControllerThread->start();
    opticalFlowCalculaterThread->start();
}

void Controller::receiveOpticalFlow(){
    cv::imshow("yy",opticalFlowCalculater->getNrom());
    this->isOpticalFlowCalculateing = false;
    this->opticalFlowFrameRate++;
}
