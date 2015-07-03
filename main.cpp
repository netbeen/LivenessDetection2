#include "mainwindow.h"
#include <QApplication>
#include <WebcamCapture.h>
#include <Controller.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller* controller = Controller::getInstance();


    MainWindow w;
    w.show();

    return a.exec();
}
