#ifndef OPENCVCAMERA_H
#define OPENCVCAMERA_H

#include <QDialog>
#include <mainwindow.h>
#include <QBuffer>
#include <QFileDialog>
#include <QCameraInfo>
#include <QCameraImageCapture>

#include <QTimer>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>

using namespace cv;

//class MainWindow;

namespace Ui {
class OpenCVCamera;
}

class OpenCVCamera : public QDialog
{
    Q_OBJECT

public:
    explicit OpenCVCamera(QWidget *parent = nullptr);
    ~OpenCVCamera();

    void SetWindowParent(MainWindow &paramWindow);

private slots:
    void initializeCameradevices();
    void openCVcameraFeed(int index);
    void OpenCameraWindow();

    void imageCaptured();
    void saveCapturedImage();
    void doneOpenCVCapture();

    void on_selectDeviceCB_currentIndexChanged(int index);
    void on_cb_resolution_currentTextChanged(const QString &arg1);
    void on_checkBox_enableSaveImg_stateChanged(int arg1);

    void getAvailableResolutions(int indexCamera);
    void getAvailableImageFormat(int indexCamera);

    void callMainwindow();


private:
    Ui::OpenCVCamera *ui;
    MainWindow *parentWindow;

    QTimer *timer;
    VideoCapture cap;

    Mat frame;
    QImage qt_image;
    QImage finalImg;
    QPixmap pixmap;

    int name;
    int width;
    int height;

};

#endif // OPENCVCAMERA_H
