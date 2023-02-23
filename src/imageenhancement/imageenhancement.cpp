#include "imageenhancement.h"
#include "ui_imageenhancement.h"


#include "mainwindow.h"
#include "ui_mainwindow.h"

ImageEnhancement::ImageEnhancement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageEnhancement)
{
    ui->setupUi(this);
}

ImageEnhancement::~ImageEnhancement()
{
    delete ui;
}

void ImageEnhancement::SetParentWindow(MainWindow* parentWindow)
{
    this->parentWindow = parentWindow;
}
