#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Controller.h>
#include <QTimer>
#include <ProgressController.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Controller* control;
    ProgressController* progressController;

signals:
    void startProgress();

public slots:
    void updateImageLabel();
    void updateInfo();
    void updateHorizontalSlider(int percentage);

private slots:
    void on_startToRunButton_clicked();
};

#endif // MAINWINDOW_H
