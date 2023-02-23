#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "imagecropperdialog.h"
#include "src/imageenhancement/imgcontrastbrightness.h"

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QRubberBand>

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPainter>
#include <QRubberBand>
#include <QElapsedTimer>

#include <QPoint>
#include <QDebug>
#include <QLabel>
#include <src/imagedetection/yolov5.h>
#include <src/imagedetection/yolov5v2.h>
#include <src/imagedetection/yolov5v3.h>
#include <src/imagefunction/imageconverter.h>
#include <src/imageenhancement/imageenhancement.h>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

#include <src/camera/opencvcamera.h>


//#pragma comment(lib,"C:\\Users\\MinebeaMitsumi\\Desktop\\GreggFolder\\openvinoopencv455\\opencv\\build\\opencv_core455.lib")
//#pragma comment(lib,"C:\\Users\\MinebeaMitsumi\\Desktop\\GreggFolder\\openvinoopencv455\\opencv\\build\\opencv_dnn455.lib")
//#pragma comment(lib,"C:\\Users\\MinebeaMitsumi\\Desktop\\GreggFolder\\openvinoopencv455\\opencv\\build\\opencv_highgui455.lib")
//#pragma comment(lib,"C:\\Users\\MinebeaMitsumi\\Desktop\\GreggFolder\\openvinoopencv455\\opencv\\build\\opencv_imgcodecs455.lib")
//#pragma comment(lib,"C:\\Users\\MinebeaMitsumi\\Desktop\\GreggFolder\\openvinoopencv455\\opencv\\build\\opencv_imgproc455.lib")
//#pragma comment(lib,"C:\\Users\\MinebeaMitsumi\\Desktop\\GreggFolder\\openvinoopencv455\\opencv\\build\\opencv_videoio455.lib")

QPixmap Mat2Image(cv::Mat src);

class OpenCVCamera;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    //    Q_PROPERTY(QImage mainwindow READ mainwindow NOTIFY imageChanged)

public:
    MainWindow(QWidget *parent = nullptr);
    //~MainWindow();
    QImage imagecapture() const;
    QLabel *lbl_sample;
    void Initialization();
    void Button_Checker();
    void Execute_Yolov5();
    void Execute_Yolov5V2();
    void Execute_Yolov5V3();

    void captureImgReceiver(const QImage &img);

signals:
    void sendQimageToCropperDialog(const QImage& _image);
    void imageChanged();

public slots:
    void receiveCropedImage(const QImage& _image);
    void updateImageCapture(const QImage& value);
    void ImageUpdate(const QPixmap& value);
    void load_result(const QImage& _image);
    void do_brightness(int val);
    void do_contrast(int val);
    void buttonStatesDisable();
    void buttonStatesEnable();

private slots:
    void on_btn_load_img_clicked();
    void on_btn_crop_img_clicked();

    void on_btn_fit_crop_clicked();

    void on_btn_detect_obj_clicked();

    void on_actionLoad_Model_triggered();

    void on_actionLoad_Class_triggered();

    void on_btn_initialization_clicked();

    void on_btn_enhancement_clicked();

    void on_btn_blob_detection_clicked();

    void on_actionOpen_Camera_triggered();

    void on_btn_edgeDetection_clicked();

    void on_btn_Laplacian_clicked();

private:
    Ui::MainWindow *ui;
    OpenCVCamera *openCVCameraUI;

    QGraphicsScene *sceneCaptured;
    QGraphicsScene *sceneResult;
    QPixmap *pixmapCaptured;;
    QImage* imgCaptured;
    ImageCropperDialog* imgCropperDialog;
    QImage* imageResult;
    YOLOV5 *yolov5;
    YOLOV5V2 *yolov5v2;
    YOLOV5V3 *yolov5v3;
    ImageConverter *imgCnvtr;
    QString onnxFile;
    QString onnxClassFile;
    bool isonnxFile =false;
    bool isonnxClassFile =false;
    bool isImgCaptureLoaded =false;
    ImageEnhancement* imgEnhancement;
    ImgContrastBrightness* conBright;
    QElapsedTimer *timer;

};
#endif // MAINWINDOW_H
