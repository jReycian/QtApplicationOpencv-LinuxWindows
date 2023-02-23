#ifndef YOLOV5V3_H
#define YOLOV5V3_H
#pragma once
#include<iostream>
#include<opencv2/opencv.hpp>

#define YOLO_P6 true

struct Output {
    int id;
    float confidence;
    cv::Rect box;
};

class YOLOV5V3
{
public:
    YOLOV5V3(){}
    ~YOLOV5V3(){}
    bool readModel(cv::dnn::Net& net, std::string& netPath, bool isCuda);
    bool Detect(cv::Mat& SrcImg,cv::dnn::Net& net,std::vector<Output>& output);
    cv::Mat drawPred(cv::Mat& img, std::vector<Output> result, std::vector<cv::Scalar> color);
    cv::Mat Execute_Detetection(std::string& modelPath,cv::Mat& srcImage);
    void Execute_ReadModel(std::string& modelPath);
    void Execute_ScalarColor(std::vector<cv::Scalar>& color);
    void Execute_PreProcess();

#if(defined YOLO_P6 && YOLO_P6==true)
    const float netAnchors[4][6] = { { 19,27, 44,40, 38,94 },{ 96,68, 86,152, 180,137 },{ 140,301, 303,264, 238,542 },{ 436,615, 739,380, 925,792 } };

    const int netWidth = 1280;
    const int netHeight = 1280;

    const int strideSize = 4;  //stride size
#else
    const float netAnchors[3][6] = { { 10,13, 16,30, 33,23 },{ 30,61, 62,45, 59,119 },{ 116,90, 156,198, 373,326 } };

    const int netWidth = 640;
    const int netHeight = 640;

    const int strideSize = 3;   //stride size
#endif // YOLO_P6

    const float netStride[4] = { 8, 16.0,32,64 };

    float boxThreshold = 0.25f;
    float classThreshold = 0.25f;

    float nmsThreshold = 0.45f;
    float nmsScoreThreshold = boxThreshold * classThreshold;

    std::vector<std::string> className = {"p_ok","p_invert"};
    //color
    cv::Scalar GREEN = cv::Scalar(0, 255, 0);
    cv::Scalar BLACK = cv::Scalar(0, 0, 0);
    cv::Scalar BLUE = cv::Scalar(255, 178, 50);
    cv::Scalar YELLOW = cv::Scalar(0, 255, 255);
    cv::Scalar RED = cv::Scalar(0, 0, 195);

private:

};

#endif // YOLOV5V3_H
