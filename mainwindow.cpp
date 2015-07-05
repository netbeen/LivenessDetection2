#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    control = Controller::getInstance();
    QObject::connect(control,SIGNAL(controllerReceivesNewImage()),this,SLOT(updateImageLabel()));

    QTimer *updateInfoTimer = new QTimer(this);
    QObject::connect(updateInfoTimer,SIGNAL(timeout()),this,SLOT(updateInfo()));
    updateInfoTimer->start(1000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateImageLabel(){
    cv::Mat rawImage = control->getRawImage();
    QImage displayImage = QImage( static_cast<const unsigned char*>(rawImage.data), rawImage.cols, rawImage.rows, QImage::Format_RGB888 );
    ui->imageLabel->setPixmap( QPixmap::fromImage(displayImage) );
}

void MainWindow::updateInfo(){
    int mainFrameRate = control->getMainFrameRate();
    ui->mainFrameRateLabel->setText(QString::number(mainFrameRate, 10));
    int faceAlignmentFrameRate = control->getFaceAlignmentFrameRate();
    ui->faceAlignmentFrameRate->setText(QString::number(faceAlignmentFrameRate, 10));
}

void MainWindow::on_pushButton_clicked()
{
    control->startToRun();
}
