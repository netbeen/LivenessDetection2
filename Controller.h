#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <WebcamCapture.h>
#include <opencv2/opencv.hpp>
#include <FaceDetector.h>
#include <EyeDetector.h>
#include <FaceAligner.h>
#include <ProgressController.h>
#include <OpticalFlowCalculater.h>


class Controller : public QObject
{
    Q_OBJECT
public:
    static Controller* getInstance();
    cv::Mat getRawImage();
    ~Controller();
    int getMainFrameRate();
    int getFaceAlignmentFrameRate();
    int getOpticalFlowFrameRate();
    void startToRun();

private:
    static Controller* ptr2Controller;
    cv::Mat rawImage;
    cv::Mat grayImage;
    cv::Mat upperImage;
    BoundingBox boundingBox;
    std::vector<cv::Rect> eyesRects;
    Controller();   //单例模式，private的构造函数


    WebcamCapture* webcamCapture;
    FaceDetector* faceDetector;
    EyeDetector* eyeDetector;
    FaceAligner* faceAligner;
    ProgressController* progressController;
    OpticalFlowCalculater* opticalFlowCalculater;

    QThread* faceAlignerThread;
    QThread* progressControllerThread;
    QThread* opticalFlowCalculaterThread;

    void drawRect(cv::Mat& input, BoundingBox& boundingBox);
    void drawRect(cv::Mat &input, std::vector<cv::Rect>& eyesRects);
    void drawPoint(cv::Mat& input, cv::Mat_<double>& shape);

    cv::Mat_<double> shape;

    bool isAligning;
    bool isShapeValid;
    bool isOpticalFlowCalculateing;
    int mainFrameRate;
    int faceAlignmentFrameRate;
    int opticalFlowFrameRate;


public slots:
    void receiveNewImage(int index);
    void receiveShape();
    void receiveOpticalFlow();

signals:
    void controllerReceivesNewImage();
    void doAlignment();
    void calcOpticalFlow();
};

#endif // CONTROLLER_H
