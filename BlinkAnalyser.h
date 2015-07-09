#ifndef BLINKANALYSER_H
#define BLINKANALYSER_H

#include <Analyser.h>
#include <vector>
//#include <Controller.h>

class BlinkAnalyser : public Analyser
{
public:
    BlinkAnalyser();
    ~BlinkAnalyser();
    virtual bool getResult() override;

public slots:
    virtual void pullNewData() override;

private:
    std::vector<bool> data;
    //Controller* controller;

};

#endif // BLINKANALYSER_H
