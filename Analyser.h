#ifndef ANALYSER_H
#define ANALYSER_H

#include <QObject>

class Analyser : public QObject
{
    Q_OBJECT
public:
    Analyser();
    ~Analyser();
    virtual bool getResult()=0;

public slots:
    virtual void pullNewData()=0;

private:
    bool isValid;
};

#endif // ANALYSER_H
