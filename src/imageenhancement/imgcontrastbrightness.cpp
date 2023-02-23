#include "imgcontrastbrightness.h"
#include "ui_imgcontrastbrightness.h"


#include "mainwindow.h"
#include "ui_mainwindow.h"

ImgContrastBrightness::ImgContrastBrightness(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImgContrastBrightness)
{
    ui->setupUi(this);
}

ImgContrastBrightness::~ImgContrastBrightness()
{
    delete ui;
}

void ImgContrastBrightness::SetParentWindow(MainWindow *myParentWindow)
{
    this->parentWindow = myParentWindow;
}

void ImgContrastBrightness::showEvent(QShowEvent *event)
{
    event->setAccepted(true);
}

void ImgContrastBrightness::resizeEvent(QResizeEvent *event)
{
    event->setAccepted(true);
}

void ImgContrastBrightness::closeEvent(QCloseEvent *event)
{
    event->setAccepted(true);
}

void ImgContrastBrightness::on_slider_brughtness_valueChanged(int value)
{
    this->parentWindow->do_brightness(value);
    ui->lbl_brightnessValue->setText(QString::number(value) + "%");
}

void ImgContrastBrightness::on_slider_contrast_valueChanged(int value)
{
    this->parentWindow->do_contrast(value);
    ui->lbl_contrastValue->setText(QString::number(value)  + "%");
}

