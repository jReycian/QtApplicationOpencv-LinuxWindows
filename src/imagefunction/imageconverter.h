#ifndef IMAGECONVERTER_H
#define IMAGECONVERTER_H
//#include <opencv2/opencv.hpp>
#include <opencv2/opencv.hpp>
#include <QImage>

using namespace cv;

class ImageConverter
{
public:
    ImageConverter();
    void qimage_to_mat(const QImage& image, cv::OutputArray out);
    void mat_to_qimage(cv::InputArray image, QImage& out);
    cv::Mat qimage2mat(const QImage& qimage);
    QImage ImageToContrast(QImage& qimage,int val);
    QImage ImageToBrightness(QImage& qimage,int val);
    QImage DrawContourOnImage(QImage& qimage);
    cv::Mat blob_detection(const cv::Mat& parseImg);
    Mat cannyEdgeDetection(const Mat &matImg);
    Mat convertToLaplacian(const Mat &imgMat);
};

#endif // IMAGECONVERTER_H
