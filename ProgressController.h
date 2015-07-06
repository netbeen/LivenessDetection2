#ifndef PROGRESSCONTROLLER_H
#define PROGRESSCONTROLLER_H

#include <QObject>
#include <iostream>
#include <QTimer>

class ProgressController : public QObject
{
    Q_OBJECT
public:
    static ProgressController* getInstance();
    ~ProgressController();

private:
    static ProgressController* ptr2ProgressController;
    ProgressController();
    const int sliderOnewayTime;
    const int edgeSleepTime;
    int horizontalSliderPercentage;
    bool horizontalSliderIsGoingLeft;
    QTimer *updateSliderTimer;
    QTimer* edgeSleepTimer;



signals:
    void updateHorizontalSlider(int percentage);

public slots:
    void startProgress();

private slots:
    void changeHorizontalSliderPercentage();
    void changeHorizontalSliderOrientation();
};

#endif // PROGRESSCONTROLLER_H
