#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <WebcamCapture.h>
#include <opencv2/opencv.hpp>
#include <FaceDetector.h>
#include <EyeDetector.h>
#include <FaceAligner.h>
#include <QMetaType>

class Controller : public QObject
{
    Q_OBJECT
public:
    static Controller* getInstance();
    cv::Mat getRawImage();
    ~Controller();
    int getMainFrameRate();
    int getFaceAlignmentFrameRate();
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

    QThread* faceAlignerThread;

    void drawRect(cv::Mat& input, BoundingBox& boundingBox);
    void drawRect(cv::Mat &input, std::vector<cv::Rect>& eyesRects);
    void drawPoint(cv::Mat& input, cv::Mat_<double>& shape);

    cv::Mat_<double> shape;

    bool isAligning;
    bool isShapeValid;
    int mainFrameRate;
    int faceAlignmentFrameRate;


public slots:
    void receiveNewImage(int index);
    void receiveShape();

signals:
    void controllerReceivesNewImage();
    void doAlignment();
};

#endif // CONTROLLER_H
