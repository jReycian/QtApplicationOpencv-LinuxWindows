#include "yolov5v3.h"

using namespace std;
using namespace cv;
using namespace cv::dnn;

YOLOV5V3 yolov5v3;
Net yolov5v3_net;
vector<Scalar> scalar_color;
//vector<Scalar> scalar_color;
//vector<Output> result;

//YOLOV5V3 test;
// Net net;

bool YOLOV5V3::readModel(Net& net,string& netPath, bool isCuda = false) {
    try {
        net = readNet(netPath);
    }
    catch (const std::exception&) {
        return false;
    }
    //cuda
    if (isCuda) {
        net.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
        net.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);
    }
    //cpu
    else {
        net.setPreferableBackend(cv::dnn::DNN_BACKEND_DEFAULT);
        net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
    }
    return true;
}
bool YOLOV5V3::Detect(Mat& SrcImg, Net& net,vector<Output>& output) {
    Mat blob;
    int col = SrcImg.cols;
    int row = SrcImg.rows;
    int maxLen = MAX(col, row);
    Mat netInputImg = SrcImg.clone();
    if (maxLen > 1.2 * col || maxLen > 1.2 * row) {
        Mat resizeImg = Mat::zeros(maxLen, maxLen, CV_8UC3);
        SrcImg.copyTo(resizeImg(Rect(0, 0, col, row)));
        netInputImg = resizeImg;
    }
    blobFromImage(netInputImg, blob, 1 / 255.0, cv::Size(netWidth, netHeight), cv::Scalar(0, 0, 0), true, false);
    //blobFromImage(netInputImg, blob, 1 / 255.0, cv::Size(netWidth, netHeight), cv::Scalar(104, 117, 123), true, false);
    //blobFromImage(netInputImg, blob, 1 / 255.0, cv::Size(netWidth, netHeight), cv::Scalar(114, 114,114), true, false);
    net.setInput(blob);
    std::vector<cv::Mat> netOutputImg;
    //vector<string> outputLayerName{"345","403", "461","output" };
    //net.forward(netOutputImg, outputLayerName[3]);
    net.forward(netOutputImg, net.getUnconnectedOutLayersNames());
#if CV_VERSION_MAJOR==4&&CV_VERSION_MINOR==6
    std::sort(netOutputImg.begin(), netOutputImg.end(), [](Mat& A, Mat& B) {return A.size[1] > B.size[1]; });//opencv 4.6
#endif
    std::vector<int> classIds;
    std::vector<float> confidences;
    std::vector<cv::Rect> boxes;
    float ratio_h = (float)netInputImg.rows / netHeight;
    float ratio_w = (float)netInputImg.cols / netWidth;
    int net_width = className.size() + 5;
    float* pdata = (float*)netOutputImg[0].data;
    for (int stride = 0; stride < strideSize; stride++) {    //stride
        int grid_x = (int)(netWidth / netStride[stride]);
        int grid_y = (int)(netHeight / netStride[stride]);
        for (int anchor = 0; anchor < 3; anchor++) {	//anchors
            //const float anchor_w = netAnchors[stride][anchor * 2];
            //const float anchor_h = netAnchors[stride][anchor * 2 + 1];
            for (int i = 0; i < grid_y; i++) {
                for (int j = 0; j < grid_x; j++) {
                    float box_score = pdata[4]; ;
                    if (box_score >= boxThreshold) {
                        cv::Mat scores(1, className.size(), CV_32FC1, pdata + 5);
                        Point classIdPoint;
                        double max_class_socre;
                        minMaxLoc(scores, 0, &max_class_socre, 0, &classIdPoint);
                        max_class_socre = (float)max_class_socre;
                        if (max_class_socre >= classThreshold) {
                            //rect [x,y,w,h]
                            float x = pdata[0];  //x
                            float y = pdata[1];  //y
                            float w = pdata[2];  //w
                            float h = pdata[3];  //h
                            int left = (x - 0.5 * w) * ratio_w;
                            int top = (y - 0.5 * h) * ratio_h;
                            classIds.push_back(classIdPoint.x);
                            confidences.push_back(max_class_socre * box_score);
                            boxes.push_back(Rect(left, top, int(w * ratio_w), int(h * ratio_h)));
                        }
                    }
                    pdata += net_width;
                }
            }
        }
    }

    //NMS
    vector<int> nms_result;
    NMSBoxes(boxes, confidences, nmsScoreThreshold, nmsThreshold, nms_result);
    for (int i = 0; i < nms_result.size(); i++) {
        int idx = nms_result[i];
        Output result;
        result.id = classIds[idx];
        result.confidence = confidences[idx];
        result.box = boxes[idx];
        output.push_back(result);
    }
    if (output.size())
        return true;
    else
        return false;
}

Mat YOLOV5V3::drawPred(Mat& img, vector<Output> result, vector<Scalar> color) {
    for (int i = 0; i < result.size(); i++) {
        int left, top;
        left = result[i].box.x;
        top = result[i].box.y;
        //int color_num = i;
        //rectangle(img, result[i].box, color[result[i].id], 2, 8);
        rectangle(img, result[i].box, GREEN, 2,3);

        string label = className[result[i].id] + ": " + to_string((int)(result[i].confidence * 100))+"%";

        int baseLine;
        Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 2, &baseLine);
        top = max(top, labelSize.height);
        //rectangle(img, Point(left, top - int(1.5 * labelSize.height)), Point(left + int(1.5 * labelSize.width), top + baseLine), Scalar(0, 255, 0), FILLED);
        rectangle(img, Point(left, top - int(1 * labelSize.height)-2), Point(left + int(1 * result[i].box.width), top + baseLine-6), GREEN, FILLED);
        putText(img, label, Point(left, top-2), FONT_HERSHEY_SIMPLEX, 0.50, RED,2);
    }
    //imshow("1", img);
    //imwrite("out.bmp", img);
    //waitKey();
    //destroyAllWindows();
    return img;
}

Mat YOLOV5V3::Execute_Detetection(string& modelPath,Mat& srcImage)
{
    //    YOLOV5V3 test;
    //     Net net;

    //            if (yolov5v3.readModel(yolov5v3_net, modelPath, false)) {
    //                cout << "read net ok!" << endl;
    //            }
    //            else {
    //                cout << "bad model" << endl;
    //                //return;
    //            }
    Execute_ReadModel(modelPath);
    Execute_ScalarColor(scalar_color);
//    vector<Scalar> color;
//    srand(time(0));
//    for (int i = 0; i < 2; i++) {
//        int b = rand() % 256;
//        int g = rand() % 256;
//        int r = rand() % 256;
//        color.push_back(Scalar(b, g, r));
//    }
    // Mat img = srcImage;
    vector<Output> result;
    if (yolov5v3.Detect(srcImage,yolov5v3_net, result)) {
        //return yolov5v3.drawPred(srcImage, result, color);
        return yolov5v3.drawPred(srcImage, result, scalar_color);
    }
    else {
        cout << "Detect Failed!"<<endl;
        return srcImage;
    }
}

void YOLOV5V3::Execute_ReadModel(string& modelPath)
{
    yolov5v3.readModel(yolov5v3_net,modelPath, false);
}

void YOLOV5V3::Execute_ScalarColor(vector<Scalar>& color)
{
        srand(time(0));
        for (int i = 0; i < 2; i++) {
            int b = rand() % 256;
            int g = rand() % 256;
            int r = rand() % 256;
            color.push_back(Scalar(b, g, r));
        }
}

void YOLOV5V3::Execute_PreProcess()
{

}
