#include "yolov5.h"

#include <fstream>
#include <iostream>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/dnn.hpp>

using namespace cv;
using namespace std;
using namespace dnn;


YOLOV5::YOLOV5(){}

void YOLOV5::load_class_lst(const QString &classPath){
    this->classPath = new QString(classPath);
    ifstream ifs(this->classPath->toStdString());
    string line;
    while (getline(ifs, line))
    {
        class_list.push_back(line);
    }
}

void YOLOV5::load_model(const QString &modelPath){
    try {
        this->onnxModel = readNetFromONNX(modelPath.toStdString());
    }  catch (exception& e) {
        QMessageBox::critical(NULL,"Error",QStringLiteral("Error load onxx file: \n 1%").arg(e.what()));
    }
//    this->onnxModel.setPreferableBackend(DNN_BACKEND_INFERENCE_ENGINE);
//    this->onnxModel.setPreferableTarget(DNN_TARGET_CPU);
}

void YOLOV5::draw_label(Mat &input_image, string label, int left, int top){
    int baseLine;
    Size label_size = getTextSize(label, FONT_FACE, FONT_SCALE, THICKNESS, &baseLine);
    top = max(top, label_size.height);
    // Top left corner.
    Point tlc = Point(left, top);
    // Bottom right corner.
    Point brc = Point(left + label_size.width, top + label_size.height + baseLine);
    // Draw white rectangle.
    rectangle(input_image, tlc, brc, GREEN, FILLED);
    // Put the label on the black rectangle.
    putText(input_image, label, Point(left, top + label_size.height), FONT_FACE, FONT_SCALE, RED, THICKNESS);
}

std::vector<Mat> YOLOV5::pre_process(Mat &input_image, Net &net){
    // Convert to blob.
    Mat blob;
    blobFromImage(input_image, blob, 1. / 255.0, Size(INPUT_WIDTH,INPUT_HEIGHT), Scalar(), true, false);
    this->onnxModel.setInput(blob);
    // Forward propagate.
    this->onnxModel.forward(outputs, this->onnxModel.getUnconnectedOutLayersNames());
    return outputs;
}

Mat YOLOV5::post_process(Mat &input_image, vector<Mat> &outputs, const vector<string> &class_name){
    // Initialize vectors to hold respective outputs while unwrapping detections.
        vector<int> class_ids;
        vector<float> confidences;
        vector<Rect> boxes;
        // Resizing factor.
        float x_factor = input_image.cols / INPUT_WIDTH;
        float y_factor = input_image.rows / INPUT_HEIGHT;
        float* data = (float*)outputs[0].data;
        const int dimensions = 7;
        // 25200 for default size 640.
        const int rows = 102000;
        // Iterate through 25200 detections.
        for (int i = 0; i < rows; ++i)
        {
            float confidence = data[4];
            // Discard bad detections and continue.
            if (confidence >= CONFIDENCE_THRESHOLD)
            {
                float* classes_scores = data + 5;
                // Create a 1x85 Mat and store class scores of 80 classes.
                Mat scores(1, class_name.size(), CV_32FC1, classes_scores);
                // Perform minMaxLoc and acquire the index of best class  score.
                Point class_id;
                double max_class_score;
                minMaxLoc(scores, 0, &max_class_score, 0, &class_id);
                // Continue if the class score is above the threshold.
                if (max_class_score > SCORE_THRESHOLD)
                {
                    // Store class ID and confidence in the pre-defined respective vectors.
                    confidences.push_back(confidence);
                    class_ids.push_back(class_id.x);
                    // Center.
                    float cx = data[0];
                    float cy = data[1];
                    // Box dimension.
                    float w = data[2];
                    float h = data[3];
                    // Bounding box coordinates.
                    int left = int((cx - 0.5 * w) * x_factor);
                    int top = int((cy - 0.5 * h) * y_factor);
                    int width = int(w * x_factor);
                    int height = int(h * y_factor);
                    // Store good detections in the boxes vector.
                    boxes.push_back(Rect(left, top, width, height));
                }
            }
            // Jump to the next row.
            data += 7;
        }

        // Perform Non-Maximum Suppression and draw predictions.
        vector<int> indices;
        NMSBoxes(boxes, confidences, SCORE_THRESHOLD, NMS_THRESHOLD, indices);
        for (int i = 0; i < indices.size(); i++)
        {
            int idx = indices[i];
            Rect box = boxes[idx];
            int left = box.x;
            int top = box.y;
            int width = box.width;
            int height = box.height;

            // Draw bounding box.
            rectangle(input_image, Point(left, top), Point(left + width, top + height), GREEN, 1 * THICKNESS);
            // Get the label for the class name and its confidence.
            string label = format("%.2f", confidences[idx]);
            label = class_name[class_ids[idx]] + ":" + label;
            // Draw class labels.
            draw_label(input_image, label, left, top);
        }
        return input_image;
}

Mat YOLOV5::parse_detetction(const Mat& parseImg){
    //Mat frame(parseImg.height(),parseImg.width(),CV_8UC4,(void *)parseImg.constBits(),parseImg.bytesPerLine());
    //Mat frame = imread("C:/Users/MinebeaMitsumi/Desktop/QTProjects/build-QTAppsOpenCV-V2-Desktop_Qt_5_12_12_MSVC2017_64bit-Debug/debug/detection/test3.bmp");
    cv::Mat OrigImg;
    parseImg.copyTo(OrigImg);
    cv::Mat OrigImgCopy(OrigImg.clone());
    vector<Mat> detections;
    detections = pre_process(OrigImg, onnxModel);
    Mat imgResult = post_process(OrigImgCopy, detections, class_list);

    vector<double> layersTimes;
    double freq = getTickFrequency() / 1000;
    double t = onnxModel.getPerfProfile(layersTimes) / freq;
    string label = format("Process time : %.2f ms", t);
    cv::putText(imgResult, label, Point(20, 40), FONT_FACE, FONT_SCALE, YELLOW);
    //cv::imwrite("C:/Users/MinebeaMitsumi/Desktop/GreggFolder/sample11.jpg",imgResult);
    return imgResult;
}

