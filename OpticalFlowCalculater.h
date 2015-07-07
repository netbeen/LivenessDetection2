#ifndef OPTICALFLOWCALCULATER_H
#define OPTICALFLOWCALCULATER_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include <cmath>

class OpticalFlowCalculater : public QObject
{
    Q_OBJECT
public:
    OpticalFlowCalculater();
    ~OpticalFlowCalculater();
    void receiveNewFrame(cv::Mat& newFrame);
    cv::Mat getNrom();
    cv::Mat getPhaseAngle();

private:
    bool preFrameVaild;
    cv::Mat preFrame;
    cv::Mat currentFrame;
    cv::Mat norm;
    cv::Mat phaseAngle;
    cv::Mat opticalFlow;

    void separateNromAndAngle(const cv::Mat& opticalFlow, cv::Mat& norm, cv::Mat& phaseAngle);

public slots:
    void calc();

signals:
    void calcCompete();
};

#endif // OPTICALFLOWCALCULATER_H
