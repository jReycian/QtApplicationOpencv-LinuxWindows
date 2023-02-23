#include "opencvcamera.h"
#include "ui_opencvcamera.h"

#include <QActionGroup>
#include <QDebug>

using namespace cv;

Q_DECLARE_METATYPE(QCameraInfo)

OpenCVCamera::OpenCVCamera(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenCVCamera)
{
    this->setFixedSize(939,559);
    ui->setupUi(this);
    ui->cb_formats->setDisabled(true);
    ui->btnProcess->setDisabled(true);
//    ui->checkBox_enableSaveImg->setDisabled(true);

    timer = new QTimer(this);
    initializeCameradevices();

    qDebug() << "Capture isAvailable: " << cap.isOpened();
    if (cap.isOpened() == false)
    {
        ui->btnCapturePhoto->setDisabled(true);
        ui->viewfinder->setText("No device detected.");
    }

    connect(ui->btnCapturePhoto, &QPushButton::clicked, this, &OpenCVCamera::imageCaptured);
    connect(ui->btnProcess, &QPushButton::clicked, this, &OpenCVCamera::doneOpenCVCapture);
}

OpenCVCamera::~OpenCVCamera()
{
    delete ui;
    cap.release();
    timer->stop();
}

void OpenCVCamera::SetWindowParent(MainWindow &paramWindow)
{
    this->parentWindow = &paramWindow;
}

void OpenCVCamera::initializeCameradevices()
{
    QActionGroup *videoDevicesGroup = new QActionGroup(this);
    videoDevicesGroup->setExclusive(true);
    const QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    for (const QCameraInfo &cameraInfo : cameras)
    {
        QAction *videoDeviceAction = new QAction(cameraInfo.description(), videoDevicesGroup);
        videoDeviceAction->setCheckable(true);
        videoDeviceAction->setData(QVariant::fromValue(cameraInfo));
        if (cameraInfo == QCameraInfo::defaultCamera())
            videoDeviceAction->setChecked(true);

        ui->selectDeviceCB->addItem(cameraInfo.description());
    }
}

void OpenCVCamera::on_cb_resolution_currentTextChanged(const QString &arg1)
{

    QString cbBoxValue = arg1;
    QStringList list = cbBoxValue.split("x");
    QVector<int> resolutions;
    for (QString number : list)
    {
        resolutions.append(number.toInt());
    }

    auto splitter = arg1.split("x");

    if (arg1 != "Default Resolution")
    {
        width = splitter[0].toInt();
        height = splitter[1].toInt();

        cap.set(CAP_PROP_FRAME_WIDTH, width);
        cap.set(CAP_PROP_FRAME_HEIGHT, height);
    }

    ui->btnProcess->setDisabled(true);
}

void OpenCVCamera::openCVcameraFeed(int index)
{
    cap.open(index);
    if (!cap.isOpened())
        qDebug() << "No device found.";
    else
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(OpenCameraWindow()));
        timer->start(0);
    }

}

void OpenCVCamera::OpenCameraWindow()
{
    if (cap.isOpened()){
        cap >> frame;
        cvtColor(frame, frame, /*CV_BGR2RGB*/COLOR_BGR2RGB);
        qt_image = QImage((frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
        pixmap = QPixmap::fromImage(qt_image);
        const int w = ui->viewfinder->width();
        const int h = ui->viewfinder->height();

        ui->viewfinder->setPixmap(pixmap.scaled(w, h, Qt::KeepAspectRatio));
    }
}

void OpenCVCamera::imageCaptured()
{
    qt_image = QImage((frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
    pixmap = QPixmap::fromImage(qt_image);
    const int w = ui->displayImage->width();
    const int h = ui->displayImage->height();
    ui->displayImage->setPixmap(pixmap.scaled(w, h, Qt::KeepAspectRatio));

    finalImg = pixmap.toImage();

    if (ui->checkBox_enableSaveImg->checkState() == 2)
        saveCapturedImage();

    ui->btnProcess->setDisabled(false);
}

void OpenCVCamera::saveCapturedImage()
{

    QString format = ui->cb_formats->currentText();
    QPixmap pixmap = QPixmap::fromImage(finalImg);

    QString filename("C:\\Users\\MinebeaMitsumi\\Pictures\\image");
    QFileInfo info(filename);
    QString dyName = info.path()  + "/" + info.baseName() + QString::number(name) + "." + format;
    QFile file(dyName);

    if (!file.open(QIODevice::WriteOnly))
        qDebug() << file.errorString();
    else
    {
        pixmap.save(dyName);
        ui->lbl_save->setText(dyName);
        name++;
    }
}

void OpenCVCamera::doneOpenCVCapture()
{
    callMainwindow();

    cap.release();
    timer->stop();
    this->~OpenCVCamera();
}

void OpenCVCamera::on_selectDeviceCB_currentIndexChanged(int index)
{
    openCVcameraFeed(index);

    ui->cb_resolution->addItem("Default Resolution");
    if (ui->cb_resolution->count() > 0)
    {
        int getIndex = ui->cb_resolution->count() - 1;

        while (getIndex > 0 )
        {
            ui->cb_resolution->removeItem(getIndex);
            getIndex--;
        }
    }
    getAvailableResolutions(index);
    getAvailableImageFormat(index);
}

void OpenCVCamera::getAvailableResolutions(int indexCamera)
{
    QList<QCameraInfo> getCameraDevice = QCameraInfo::availableCameras();
    if (getCameraDevice.count() > 0)
    {
        QCameraInfo cameraDevice = getCameraDevice[indexCamera];
        QCamera *camera  = new QCamera(cameraDevice);
        camera->load();

        QCameraImageCapture *image_capture = new QCameraImageCapture(camera);
        QList<QSize> resolution = image_capture->supportedResolutions();

        for (const QSize &resolutions : resolution)
        {
            ui->cb_resolution->addItem(QString("%1x%2").arg(resolutions.width()).arg(resolutions.height()),
                                       QVariant(resolutions));
        }
    }
}

void OpenCVCamera::getAvailableImageFormat(int indexCamera)
{
    QList<QCameraInfo> getCameraDevice = QCameraInfo::availableCameras();
    if (getCameraDevice.count() > 0)
    {
        QCameraInfo cameraDevice = getCameraDevice[indexCamera];
        QCamera *camera  = new QCamera(cameraDevice);
        camera->load();

        QCameraImageCapture *image_capture = new QCameraImageCapture(camera);
        QStringList format = image_capture->supportedImageCodecs();

        for (const QString &formats : format)
        {
            QString description = image_capture->imageCodecDescription(formats);
            ui->cb_formats->addItem(formats + description, QVariant(formats));
        }
    }
}

void OpenCVCamera::callMainwindow()
{
    parentWindow->captureImgReceiver(finalImg);
}

void OpenCVCamera::on_checkBox_enableSaveImg_stateChanged(int arg1)
{
    if (arg1 == 0)
    {
        ui->cb_formats->setDisabled(true);
        ui->lbl_save->setText("");
    }
    else
        ui->cb_formats->setDisabled(false);

}
