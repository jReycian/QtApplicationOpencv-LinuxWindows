#include "yolov5v2.h"
using namespace std;
using namespace cv;
using namespace dnn;



void YOLOV5V2::Initialization(NetConfig conf)
{
    this->confTHreshold = conf.confthreshold;
    this->nmsThreshold = conf.nmsThreshold;
    this->objThreshold = conf.objThreshold;
    classIds.reserve(20);
    confidences.reserve(20);
    boxes.reserve(20);
    outs.reserve(3);
}

bool YOLOV5V2::loadModel(const char *onnxfile)
{
    try {
        this->net = readNetFromONNX(onnxfile);
        return true;
    }  catch (exception& e) {
        QMessageBox::critical(NULL,"Error",QStringLiteral("Error onxx file: 1%").arg(e.what()));
        return false;
    }
    //    this->net.setPreferableBackend(DNN_TARGET_OPENCL);
    //    this->net.setPreferableTarget(DNN_TARGET_CPU);
    this->net.setPreferableBackend(DNN_BACKEND_DEFAULT);
    this->net.setPreferableTarget(DNN_TARGET_CPU);
}

Mat YOLOV5V2::detect(cv::Mat &frame)
{
    blobFromImage(frame,blob,1/255.0,Size(this->inpWidth,this->inpHeight),Scalar(0,0,0),true,false);
    this->net.setInput(blob);
    this->net.forward(outs,this->net.getUnconnectedOutLayersNames());
    classIds.clear();
    confidences.clear();
    boxes.clear();
    float ratioh = (float)frame.rows/this->inpHeight,ratiow = (float)frame.cols/this->inpWidth;
    int n=0,q=0,i=0,j=0,nout=8+5,c=0;
    for (n=0;n<3;n++){
        int num_grid_x = (int)(this->inpWidth/this->stride[n]);
        int num_grid_y = (int)(this->inpHeight/this->stride[n]);
        int area = num_grid_x* num_grid_y;
        this->sigmoid(&outs[n],3 * nout * area);
        for(q=0;q<3;q++){
            const float anchor_w = this->anchors[n][q*2];
            const float anchor_h = this->anchors[n][q*2+1];
            float * pdata = (float*)outs[n].data+q * nout * area;

            for(i=0;i<num_grid_y;i++){
                for(j=0;j<num_grid_x;j++){
                    float box_score = pdata[4 * area + i * num_grid_x+j];
                    if(box_score > this->objThreshold){
                        float max_class_score =0,class_score=0;
                        int max_class_id=0;
                        for(c=0;c<2;c++){//2 is number of classes
                            class_score=pdata[(c+5)*area+i*num_grid_x+j];
                            if(class_score > max_class_score){
                                max_class_score=class_score;
                                max_class_id =c;
                            }
                        }
                        if(max_class_score > this->confTHreshold){
                            float cx = (pdata[i* num_grid_x+j]*2.f-0.5f+j)* this->stride[n];
                            float cy = (pdata[area+i* num_grid_x+j]*2.f-0.5f+i)* this->stride[n];
                            float w = powf(pdata[2*area + i * num_grid_x+j]*2.f,2.f)* anchor_w;
                            float h = powf(pdata[3*area + i * num_grid_x+j]*2.f,2.f)* anchor_h;

                            int left =(cx-0.5*w)*ratiow;
                            int top =(cy-0.5*h)*ratioh;

                            classIds.push_back(max_class_id);
                            confidences.push_back(max_class_score);
                            boxes.push_back(Rect(left,top,(int)(w*ratiow),(int)(h*ratioh)));
                        }
                    }
                }
            }
        }
    }

    vector<int> indices;
    NMSBoxes(boxes,confidences,this->confTHreshold,this->nmsThreshold,indices);
    for(size_t i=0;i <indices.size();++i){
        int idx = indices[i];
        Rect box = boxes[idx];
        this->drawPred(classIds[idx],confidences[idx],box.x,box.y,box.x+box.width,box.y+box.height,frame);
    }
    return frame;
}

void YOLOV5V2::drawPred(int classId, float conf, int left, int top, int right, int bottom, cv::Mat &frame)
{
    rectangle(frame,Point(left,top),Point(right,bottom),Scalar(0,0,255),3);
    string label = format("%.2f",conf);
    label = this->classes[classId]+ ":"+label;

    int baseline;
    Size labelSize = getTextSize(label,FONT_HERSHEY_SIMPLEX,0.5,1,& baseline);
    top = max(top,labelSize.height);
    putText(frame,label,Point(left,top),FONT_HERSHEY_SIMPLEX,0.75,Scalar(0,255,0),1);
}

void YOLOV5V2::sigmoid(cv::Mat *out, int length)
{
    float* pdata = (float*)(out->data);
    int i =0;
    for(i=0;i<length;i++){
        pdata[i]=1.0 / (1+expf(-pdata[i]));
    }
}
