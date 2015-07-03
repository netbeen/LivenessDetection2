#-------------------------------------------------
#
# Project created by QtCreator 2015-06-30T23:01:41
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LivenessDetection2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    WebcamCapture.cpp \
    Controller.cpp \
    BoundingBox.cpp \
    FaceDetector.cpp \
    Detector.cpp \
    EyeDetector.cpp \
    FaceAligner.cpp \
    ESR/Fern.cpp \
    ESR/FernCascade.cpp \
    ESR/ShapeRegressor.cpp \
    ESR/Utils.cpp

HEADERS  += mainwindow.h \
    WebcamCapture.h \
    Controller.h \
    BoundingBox.h \
    FaceDetector.h \
    Detector.h \
    EyeDetector.h \
    FaceAligner.h \
    ESR.hpp

FORMS    += mainwindow.ui

LIBS += /usr/local/lib/libopencv_core.so    \
		/usr/local/lib/libopencv_imgproc.so \
		/usr/local/lib/libopencv_highgui.so \
		/usr/local/lib/libopencv_objdetect.so \
