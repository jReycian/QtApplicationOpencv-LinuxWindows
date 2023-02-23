#ifndef IMAGECROPPERDIALOG_H
#define IMAGECROPPERDIALOG_H


#include <QDialog>
#include <QWidget>
#include <QBoxLayout>
#include <QGraphicsView>
#include <QMainWindow>


#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

class ImageCropper;
class QLabel;
class MainWindow;

namespace Ui {
class ImageCropperDialog;
}

class ImageCropperDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImageCropperDialog(QWidget *parent = nullptr);
    ~ImageCropperDialog();
    void SetParentWindow(MainWindow *myParentWindow);
signals:
    //void valueQImageChanged(const QImage& _image);
    void sendCroppedImage(const QImage& _image);

public slots:
    void receiveQimageValue(const QImage& _image);
    //void setQimageValue(const QImage& _image);
    void donecropping();

private slots:
    void crop();

private:
    Ui::ImageCropperDialog *ui;
    ImageCropper* m_imageCropper;
    QLabel* m_croppedImage;
    QImage imgValue;
    //QPixmap imgValue;
    QVBoxLayout *layout_crop_left;
    QLayout *parent_layout;
    QGraphicsView *grph_crop_result;
    QGraphicsScene *sceneCropped;
    MainWindow *parentWindow;
    bool isCropClicked;
     QPushButton* cropBtnDone;
};

#endif // IMAGECROPPERDIALOG_H
