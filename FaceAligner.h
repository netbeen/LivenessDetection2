#ifndef FACEALIGNER_H
#define FACEALIGNER_H

#include <opencv2/opencv.hpp>
#include <ESR.hpp>
#include <QObject>
#include <QThread>

class FaceAligner : public QObject
{
    Q_OBJECT
public:
    FaceAligner();
    ~FaceAligner();
    cv::Mat_<double> align(cv::Mat& grayImg, BoundingBox& boundingBox);
    cv::Mat_<double> getCurrentShape();
    void setNextFrame(cv::Mat& grayImg, BoundingBox& boundingBox);

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
    void doAlignment();
};

#endif // FACEALIGNER_H
