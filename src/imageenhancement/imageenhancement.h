#ifndef IMAGEENHANCEMENT_H
#define IMAGEENHANCEMENT_H

#include <QDialog>

class MainWindow;

namespace Ui {
class ImageEnhancement;
}

class ImageEnhancement : public QDialog
{
    Q_OBJECT

public:
    explicit ImageEnhancement(QWidget *parent = nullptr);
    ~ImageEnhancement();
    void SetParentWindow(MainWindow* parentWindow);

private:
    Ui::ImageEnhancement *ui;
    MainWindow *parentWindow;
};

#endif // IMAGEENHANCEMENT_H
