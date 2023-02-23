#ifndef IMGCONTRASTBRIGHTNESS_H
#define IMGCONTRASTBRIGHTNESS_H

#include <QDialog>
#include <QMainWindow>

class MainWindow;

namespace Ui {
class ImgContrastBrightness;
}

class ImgContrastBrightness : public QDialog
{
    Q_OBJECT

public:
    explicit ImgContrastBrightness(QWidget *parent = nullptr);
    ~ImgContrastBrightness();
    void SetParentWindow(MainWindow *myParentWindow);
    void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *ev);
    void closeEvent(QCloseEvent *event);

signals:

private slots:
    void on_slider_brughtness_valueChanged(int value);

    void on_slider_contrast_valueChanged(int value);

private:
    Ui::ImgContrastBrightness *ui;
    MainWindow *parentWindow;
};

#endif // IMGCONTRASTBRIGHTNESS_H
