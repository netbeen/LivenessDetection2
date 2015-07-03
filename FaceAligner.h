#ifndef FACEALIGNER_H
#define FACEALIGNER_H

#include <opencv2/opencv.hpp>
#include <ESR.hpp>
#include <QObject>
#include <QThread>

class FaceAligner : public QThread
{
    Q_OBJECT
public:
    FaceAligner();
    ~FaceAligner();
    cv::Mat_<double> align(cv::Mat& grayImg, BoundingBox& boundingBox);
    virtual void run();
    cv::Mat_<double> getCurrentShape();

private:
    const int initial_number;
    const int landmarkNum;
    ShapeRegressor regressor;
    cv::Mat_<double> currentShape;

    cv::Mat grayImg;
    BoundingBox boundingBox;
    bool receiveNewData;

signals:
    void alignmentCompete();

public slots:
    void doAlignment(cv::Mat& grayImg, BoundingBox& boundingBox);
};

#endif // FACEALIGNER_H
