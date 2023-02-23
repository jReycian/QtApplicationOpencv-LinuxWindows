#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>

#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

//using namespace cv;
using namespace std;
using namespace std::chrono;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Initialization();
    this->setObjectName("MyMainWindow");

    buttonStatesDisable();
}

//MainWindow::~MainWindow()
//{
//   delete ui;
//}

QImage MainWindow::imagecapture() const
{
    return *imgCaptured;
}

void MainWindow::Initialization()
{
    imgCnvtr = new ImageConverter();
    //    yolov5 = new YOLOV5();
    //    yolov5v2 = new YOLOV5V2();
    sceneResult =  new QGraphicsScene(this);

    //disable some buttons
    //    if(!isImgCaptureLoaded){
    //        ui->btn_detect_obj->setEnabled(false);
    //        ui->btn_fit_crop->setEnabled(false);
    //        ui->btn_crop_img->setEnabled(false);
    //    }
    //    if(onnxFile.isEmpty() || onnxFile.isNull()){
    //        onnxFile = QCoreApplication::applicationDirPath()+"/config_files/exp_model.onnx";
    //    }
    //    if(onnxClassFile.isEmpty() || onnxClassFile.isNull()){
    //        onnxClassFile =  QCoreApplication::applicationDirPath()+"/config_files/modelclass.txt";
    //    }
}

void MainWindow::Button_Checker()
{
    //    if(isonnxFile && isonnxClassFile && isImgCaptureLoaded) {ui->btn_detect_obj->setEnabled(true);}
}

void MainWindow::Execute_Yolov5()
{
    //    cv::Mat ConvrtQimgToMat(imgCnvtr->qimage2mat(*imgCaptured));
    //    //cv::imwrite("C:/Users/MinebeaMitsumi/Desktop/GreggFolder/sample222.jpg",ConvrtQimgToMat);
    //    QImage resultImg;
    //    auto start = high_resolution_clock::now();
    //    imgCnvtr->mat_to_qimage(yolov5->parse_detetction(ConvrtQimgToMat),resultImg);
    //    auto end = high_resolution_clock::now();
    //    duration<double,milli> elapse= end - start;
    //    //cv::Mat ConvrtQimgToMatResult(imgCnvtr->qimage2mat(*resultImg));
    //    //cv::imwrite("C:/Users/MinebeaMitsumi/Desktop/GreggFolder/sample333.jpg",imgCnvtr->qimage2mat(*resultImg));
    //    //imgCnvtr->mat_to_qimage(yolov5->parse_detetction(ConvrtQimgToMat),*this->imageResult);
    //    this->imageResult =new QImage(resultImg);
    //    load_result(*imageResult);
    //    ui->lbl_result_time->setText(QString("%1 ms").arg(elapse.count()));
}

void MainWindow::Execute_Yolov5V2()
{
    //    NetConfig confg;
    //    NetConfig *yolo_nets = new NetConfig[4]
    //    {
    //    {0.5,0.5,0.5,"yolov5s"},
    //    {0.5,0.5,0.5,"yolov5m"},
    //    {0.5,0.5,0.5,"yolov5l"},
    //    {0.5,0.5,0.5,"yolov5x"}
    //};
    //    cv::Mat ConvrtQimgToMat(imgCnvtr->qimage2mat(*imgCaptured));
    //    yolov5v2->Initialization(yolo_nets[0]);
    //    yolov5v2->loadModel(onnxFile.toStdString().c_str());

    //    cv::Mat MatResult = yolov5v2->detect(ConvrtQimgToMat);

}

void MainWindow::Execute_Yolov5V3()
{
    //    QImage resultImg;
    //    //cv::Mat ConvrtQimgToMat(imgCnvtr->qimage2mat(QImage(QCoreApplication::applicationDirPath()+"/detection/test2.jpg")));
    //    cv::Mat ConvrtQimgToMat(imgCnvtr->qimage2mat(imagecapture()));
    //    string stdonnx(onnxFile.toStdString());
    //    auto start = high_resolution_clock::now();
    //    //yolov5v3->Execute_Detetection(stdonnx,ConvrtQimgToMat);
    //    imgCnvtr->mat_to_qimage(yolov5v3->Execute_Detetection(stdonnx,ConvrtQimgToMat), resultImg);
    //    auto end = high_resolution_clock::now();
    //    duration<double,milli> elapse= end - start;
    //    qDebug() << QString("result: 1%").arg(elapse.count());
    //    //    if(yolov5v3->Execute_ReadModel(stdonnx)){
    //    //        yolov5v3->Execute_ScalarColor();
    //    ////        auto start = high_resolution_clock::now();
    //    ////        yolov5v3->Execute_Detetction(stdonnx,ConvrtQimgToMat);
    //    ////        auto end = high_resolution_clock::now();
    //    //        duration<double,milli> elapse= end - start;
    //    //        qDebug() << QString("result: 1%").arg(elapse.count());
    //    //    }else{
    //    //        qDebug() << "Went wrong....";
    //    //    }
    //    this->imageResult =new QImage(resultImg);
    //    load_result(*imageResult);

}

void MainWindow::captureImgReceiver(const QImage &img)
{
    sceneCaptured = new QGraphicsScene(this);
    imgCaptured = new QImage(img);
    sceneCaptured->addPixmap(QPixmap::fromImage(*imgCaptured));
    ui->grph_capture_view->setScene(sceneCaptured);
    ui->grph_capture_view->fitInView(sceneCaptured->itemsBoundingRect());
    load_result(*imgCaptured);

    qDebug() << "Image Data isNull: " << imgCaptured->isNull();

    if (imgCaptured->isNull())
        buttonStatesDisable();
    else
        buttonStatesEnable();
}


void MainWindow::on_btn_load_img_clicked()
{
    //    sceneCaptured =  new QGraphicsScene(this);
    //    imgCaptured = new QImage(QCoreApplication::applicationDirPath()+"/detection/0001b.jpg");

    //    //imgCaptured = new QImage("C:/Users/MinebeaMitsumi/Desktop/GreggFolder/test1.jpg");
    //    //pixmapCaptured =  new QPixmap("C:/Users/MinebeaMitsumi/Desktop/GreggFolder/test1.jpg");

    //    sceneCaptured->addPixmap(QPixmap::fromImage(*imgCaptured));
    //    ui->grph_capture_view->setScene(sceneCaptured);
    //    ui->grph_capture_view->fitInView(sceneCaptured->itemsBoundingRect());

    //    //ui->label_5->setPixmap(QPixmap::fromImage(cls->imgValueCropCap));

    //    isImgCaptureLoaded = true;
    ////    ui->btn_fit_crop->setEnabled(true);
    ////    ui->btn_crop_img->setEnabled(true);
}


void MainWindow::on_btn_crop_img_clicked()
{
    //connect(this,SIGNAL(sendQimageToCropperDialog(QImage)),imgCropperDialog,SLOT(receiveQimageValue(QImage)));
    //emit sendQimageToCropperDialog(*imgCaptured);
    imgCropperDialog = new ImageCropperDialog(this);
    imgCropperDialog->SetParentWindow(this);
    imgCropperDialog->receiveQimageValue(*imgCaptured);
    imgCropperDialog->setWindowTitle("Cropping Image");
    imgCropperDialog->setModal(true);
    imgCropperDialog->exec();
}

void MainWindow::receiveCropedImage(const QImage& _image){

    imgCaptured = new QImage(_image);
    sceneCaptured = new QGraphicsScene(this);
    sceneCaptured->addPixmap(QPixmap::fromImage(*imgCaptured));
    ui->grph_capture_view->setScene(sceneCaptured);
    ui->grph_capture_view->fitInView(sceneCaptured->itemsBoundingRect());
    load_result(*imgCaptured);
    //ImageUpdate(QPixmap::fromImage(*imgCaptured));
    //    cv::Mat ConvrtQimgToMat(imgCnvtr->qimage2mat(*imgCaptured));
    //    cv::imwrite("C:/Users/MinebeaMitsumi/Desktop/GreggFolder/sample111.jpg",ConvrtQimgToMat);
}

void MainWindow::updateImageCapture(const QImage &value)
{
    emit imageChanged();
}

void MainWindow::ImageUpdate(const QPixmap &value)
{
    sceneCaptured =  new QGraphicsScene(this);
    sceneCaptured->addPixmap(QPixmap::fromImage(*imgCaptured));
    ui->grph_capture_view->setScene(sceneCaptured);
    ui->grph_capture_view->fitInView(sceneCaptured->itemsBoundingRect());
}

void MainWindow::load_result(const QImage& _image)
{
    //    imageResult = new QImage(_image);
    sceneResult =  new QGraphicsScene(this);
    sceneResult->addPixmap(QPixmap::fromImage(_image));
    ui->grph_detect_result->setScene(sceneResult);
    ui->grph_detect_result->fitInView(sceneResult->itemsBoundingRect());
}

void MainWindow::do_brightness(int val)
{
    QImage toBrightness;
    toBrightness = *imgCaptured;
    toBrightness = imgCnvtr->ImageToBrightness(toBrightness,val);
    load_result(toBrightness);
}

void MainWindow::do_contrast(int val)
{
    QImage toContrast;
    toContrast = *imgCaptured;
    toContrast = imgCnvtr->ImageToContrast(toContrast,val);
    load_result(toContrast);
}

void MainWindow::on_btn_fit_crop_clicked()
{
    sceneCaptured =  new QGraphicsScene(this);
    sceneCaptured->addPixmap(QPixmap::fromImage(*imgCaptured));
    ui->grph_capture_view->setScene(sceneCaptured);
    ui->grph_capture_view->fitInView(sceneCaptured->itemsBoundingRect());
}


void MainWindow::on_btn_detect_obj_clicked()
{
    //Execute_Yolov5();
    //Execute_Yolov5V2();
    //Execute_Yolov5V3();
    load_result(imgCnvtr->DrawContourOnImage(*imgCaptured));
}


void MainWindow::on_actionLoad_Model_triggered()
{
    onnxFile = QFileDialog::getOpenFileName(this,QStringLiteral("Choose onnx file"),".","*.onnx");
    if(!QFile::exists(onnxFile)){
        return;
    }
    //    isonnxFile =true;
    //    Button_Checker();
}


void MainWindow::on_actionLoad_Class_triggered()
{
    onnxClassFile = QFileDialog::getOpenFileName(this,QStringLiteral("Choose class file"),".","*.txt");
    if(!QFile::exists(onnxClassFile)){
        return;
    }
    //    isonnxClassFile =true;
    //    Button_Checker();
}

void MainWindow::on_btn_initialization_clicked()
{
    //    yolov5->load_model(onnxFile);
    //    yolov5->load_class_lst(onnxClassFile);
}


void MainWindow::on_btn_enhancement_clicked()
{
    imageResult = imgCaptured;
    load_result(*imageResult);
    conBright = new ImgContrastBrightness(this);
    conBright->SetParentWindow(this);
    conBright->setWindowTitle("Image Enhancement");
    conBright->exec();
}


void MainWindow::on_btn_blob_detection_clicked()
{
    imageResult = imgCaptured;
    auto start = high_resolution_clock::now();
    cv::Mat ConvrtQimgToMat(imgCnvtr->qimage2mat(*imageResult));
    cv::Mat blobResult(imgCnvtr->blob_detection(ConvrtQimgToMat));
    QImage resultImg;
    imgCnvtr->mat_to_qimage(blobResult,resultImg);
    this->imageResult =new QImage(resultImg);
    load_result(*imageResult);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    ui->lbl_result_time->setText(QString::number(duration.count()));
}


void MainWindow::on_actionOpen_Camera_triggered()
{
    openCVCameraUI = new OpenCVCamera;
    openCVCameraUI->SetWindowParent(*this);
    openCVCameraUI->setWindowTitle("OpenCV Camera");
    openCVCameraUI->setModal(true);
    openCVCameraUI->exec();
}


void MainWindow::on_btn_edgeDetection_clicked()
{

    imageResult = imgCaptured;
    auto start = high_resolution_clock::now();
    Mat imageToMat(imgCnvtr->qimage2mat(*imageResult));
    Mat cannyEdgeResult(imgCnvtr->cannyEdgeDetection(imageToMat));
    QImage cannyResult;
    imgCnvtr->mat_to_qimage(cannyEdgeResult, cannyResult);
    this->imageResult = new QImage(cannyResult);
    load_result(*imageResult);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    ui->lbl_result_time->setText(QString::number(duration.count()));
}

void MainWindow::on_btn_Laplacian_clicked()
{
    imageResult = imgCaptured;
    auto start = high_resolution_clock::now();
    Mat imgToMat(imgCnvtr->qimage2mat(*imageResult));
    Mat laplacianResult(imgCnvtr->convertToLaplacian(imgToMat));

    QImage laplacian_result;
    imgCnvtr->mat_to_qimage(laplacianResult, laplacian_result);

    this->imageResult = new QImage(laplacian_result);
    load_result(*imageResult);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    ui->lbl_result_time->setText(QString::number(duration.count()));
}

void MainWindow::buttonStatesDisable()
{
    ui->btn_crop_img->setDisabled(true);
    ui->btn_load_img->setDisabled(true);
    ui->btn_initialization->setDisabled(true);
    ui->btn_fit_crop->setDisabled(true);
    ui->btn_enhancement->setDisabled(true);
    ui->btn_edgeDetection->setDisabled(true);
    ui->btn_detect_obj->setDisabled(true);
    ui->btn_blob_detection->setDisabled(true);
    ui->btn_Laplacian->setDisabled(true);
}

void MainWindow::buttonStatesEnable()
{
    ui->btn_crop_img->setDisabled(false);
    ui->btn_enhancement->setDisabled(false);
    ui->btn_edgeDetection->setDisabled(false);
    ui->btn_detect_obj->setDisabled(false);
    ui->btn_blob_detection->setDisabled(false);
    ui->btn_Laplacian->setDisabled(false);
}



