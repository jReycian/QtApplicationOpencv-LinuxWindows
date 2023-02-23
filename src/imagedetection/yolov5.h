#ifndef YOLOV5_H
#define YOLOV5_H
#include <QString>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>
#include <QImage>
#include <QMessageBox>


class YOLOV5
{
public:
    YOLOV5();
    void load_class_lst(const QString& classPath);
    void load_model(const QString& modelPath);
    void draw_label(cv::Mat& input_image, std::string label, int left, int top);
    std::vector<cv::Mat> pre_process(cv::Mat& input_image, cv::dnn::Net& net);
    cv::Mat post_process(cv::Mat& input_image, std::vector<cv::Mat>& outputs, const std::vector<std::string>& class_name);
    cv::Mat parse_detetction(const cv::Mat& parseImg);

private:
    const float INPUT_WIDTH = 1280.0f;
    const float INPUT_HEIGHT = 1280.0f;
    const float SCORE_THRESHOLD = 0.1f;
    const float NMS_THRESHOLD = 0.10f;
    const float CONFIDENCE_THRESHOLD = 0.10f;

    const float FONT_SCALE = 0.7f;
    const int FONT_FACE = cv::FONT_HERSHEY_SIMPLEX;
    const int THICKNESS = 2;

    cv::Scalar BLACK = cv::Scalar(0, 0, 0);
    cv::Scalar BLUE = cv::Scalar(255, 178, 50);
    cv::Scalar YELLOW = cv::Scalar(0, 255, 255);
    cv::Scalar RED = cv::Scalar(0, 0, 195);
    cv::Scalar GREEN = cv::Scalar(0, 255, 0);


    cv::dnn::Net onnxModel;
    QString *classPath;
    std::vector<cv::Mat> outputs;
    std::vector<std::string> class_list;
};

#endif // YOLOV5_H
