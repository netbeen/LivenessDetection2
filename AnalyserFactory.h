#ifndef ANALYSERFACTORY_H
#define ANALYSERFACTORY_H

#include <QObject>
#include <BlinkAnalyser.h>
#include <set>
#include <string>



class AnalyserFactory : public QObject
{
    Q_OBJECT
public:
    AnalyserFactory();
    ~AnalyserFactory();
    std::set<std::string> analyserType;
    static Analyser* createAnalyser(std::string);

};

#endif // ANALYSERFACTORY_H
