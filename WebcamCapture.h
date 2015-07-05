#ifndef WEBCAMCAPTURE_H
#define WEBCAMCAPTURE_H

#include <QThread>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <QObject>
#include <vector>

class WebcamCapture:public QThread
{
    Q_OBJECT

public:
    WebcamCapture();
    ~WebcamCapture();
    virtual void run();
    int size();
    cv::Mat getImageByIndex(int index);

signals:
    void newImageCaptured(int);

private:
    cv::VideoCapture cap;
    std::vector<cv::Mat> matVector;


};

#endif // WEBCAMCAPTURE_H
