#include "imagecropperdialog.h"
#include "ui_imagecropperdialog.h"
#include "src/imagecropper/imagecropper.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QGraphicsView>
#include <QGridLayout>


ImageCropperDialog::ImageCropperDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageCropperDialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    isCropClicked=false;

    m_imageCropper = new ImageCropper(this);
    m_imageCropper->resize( 380, 380 );//default 600x600
    m_imageCropper->setProportion(QSize(4,3));
    //m_imageCropper->setImage(QPixmap("C:/Users/MinebeaMitsumi/Desktop/GreggFolder/test1.jpg"));
    m_imageCropper->setImage(QPixmap::fromImage(imgValue));
    m_imageCropper->setBackgroundColor( Qt::lightGray );
    m_imageCropper->setCroppingRectBorderColor( Qt::magenta);
    m_imageCropper->setFixedSize(395,380);
    //create programatic checkbox
    //    QCheckBox* fixedProportionsCombo = new QCheckBox("Fix proportion to (4x3)", this);
    //    connect(fixedProportionsCombo, SIGNAL(toggled(bool)),
    //            m_imageCropper, SLOT(setProportionFixed(bool)));
    //create programatic button
    //QPushButton* cropBtn = new QPushButton("Crop", this);
    //connect(cropBtn, SIGNAL(clicked()), this, SLOT(crop()));
    //place holde to display image
    //m_croppedImage = new QLabel(this);
    //define layout sequence
    QVBoxLayout *layout_v = new QVBoxLayout(this);
    // add layout vertical properties
    QHBoxLayout *layout_h = new QHBoxLayout(this);
    QPushButton* cropBtn = new QPushButton("Crop", this);
    connect(cropBtn, SIGNAL(clicked()), this, SLOT(crop()));
    cropBtnDone = new QPushButton("Cancel", this);
    connect(cropBtnDone, SIGNAL(clicked()), this, SLOT(donecropping()));
    // add layout horizontal properties
    layout_h->addWidget(cropBtn);
    layout_h->addWidget(cropBtnDone);
    //add widgets
    layout_v->addWidget(m_imageCropper);
    layout_v->addLayout(layout_h);
    window()->layout()->setSizeConstraint(QLayout::SetMinAndMaxSize);


    //layout_v->addWidget(fixedProportionsCombo);
    //layout_v->addWidget(cropBtn);
    //layout_v->addWidget(m_croppedImage);

    // QHBoxLayout *layout_right = new QHBoxLayout(this);
    //    grph_crop_result = new QGraphicsView(this);
    //    grph_crop_result->resize(380,380);
    //    layout_right->addWidget(grph_crop_result);

    //QHBoxLayout *layout_main = new QHBoxLayout(this);
    //layout_main->addLayout(layout_v);
    //layout_main->addLayout(layout_right);

    //QGridLayout *grd_layout = new QGridLayout(this);
    //grd_layout->addWidget(grph_crop_result,0,0);
    //grd_layout->addLayout(layout_right,0,1);


    //connect(this,SIGNAL(setQimageValue(QImage)),this,SLOT(setQimageValue(QImage)));

}

ImageCropperDialog::~ImageCropperDialog()
{
    delete ui;
}

void ImageCropperDialog::SetParentWindow(MainWindow* myParentWindow)
{
    parentWindow = myParentWindow;
}

void ImageCropperDialog::crop()
{
    //m_croppedImage->setPixmap(m_imageCropper->cropImage());
    isCropClicked = true;
    sceneCropped = new QGraphicsScene(this);
    sceneCropped->addPixmap(m_imageCropper->cropImage());
    ui->crop_result_grphvw->setScene(sceneCropped);
    ui->crop_result_grphvw->fitInView(sceneCropped->itemsBoundingRect());
    cropBtnDone->setText("Done");
}

void ImageCropperDialog::donecropping()
{
    if(isCropClicked){
        parentWindow->receiveCropedImage(m_imageCropper->cropImage().toImage());
    }else{
        parentWindow->receiveCropedImage(imgValue);
    }
    this->close();
}

void ImageCropperDialog::receiveQimageValue(const QImage& _image)
{
    imgValue = _image;
    m_imageCropper->setImage(QPixmap::fromImage(imgValue));
}

