#ifndef YOLOV5V2_H
#define YOLOV5V2_H
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>
#include <QMessageBox>


struct NetConfig{
    float confthreshold;
    float nmsThreshold;
    float objThreshold;
    std::string netname;
};

class YOLOV5V2
{
public:
    YOLOV5V2(){}
    void Initialization(NetConfig conf);
    bool loadModel(const char* onnxfile);
    cv::Mat detect(cv::Mat& frame);
private:
    const float anchors[3][6]={
        {10.0,13.0,16.0,20.0,33.0,23.0},
        {30.0,61.0,62.0,45.0,59.0,119.0},
        {116.0,90.0,156.0,198.0,373.0,326.0}
    };
    const float stride[4]={8.0,16.0,32.0,64.0};
    std::string classes[2]={"p_ok","p_invert"};
    const int inpWidth = 1280;
    const int inpHeight = 1280;
    float confTHreshold,nmsThreshold,objThreshold;
    cv::Mat blob;
    std::vector<cv::Mat> outs;
    std::vector<int> classIds;
    std::vector<float> confidences;
    std::vector<cv::Rect> boxes;
    cv::dnn::Net net;
    void drawPred(int classId,float conf,int left,int top,int right,int bottom,cv::Mat& frame);
    void sigmoid(cv::Mat *out,int length);
};

static inline float sigmoid_x(float x){
    return static_cast<float>(1.f/ (1.f+exp(-x)));
}

#endif // YOLOV5V2_H
