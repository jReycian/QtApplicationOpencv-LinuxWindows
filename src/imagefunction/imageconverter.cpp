#include "imageconverter.h"

using namespace std;
using namespace cv;

ImageConverter::ImageConverter()
{

}

void ImageConverter::qimage_to_mat(const QImage &image, cv::OutputArray out)
{
    switch(image.format()) {
    case QImage::Format_Invalid:
    {
        cv::Mat empty;
        empty.copyTo(out);
        break;
    }
    case QImage::Format_RGB32:
    {
        cv::Mat view(image.height(),image.width(),CV_8UC4,(void *)image.constBits(),image.bytesPerLine());
        view.copyTo(out);
        break;
    }
    case QImage::Format_RGB888:
    {
        cv::Mat view(image.height(),image.width(),CV_8UC3,(void *)image.constBits(),image.bytesPerLine());
        cvtColor(view, out, cv::COLOR_RGB2BGR);
        break;
    }
    default:
    {
        QImage conv = image.convertToFormat(QImage::Format_ARGB32);
        cv::Mat view(conv.height(),conv.width(),CV_8UC4,(void *)conv.constBits(),conv.bytesPerLine());
        view.copyTo(out);
        break;
    }
    }
}

void ImageConverter::mat_to_qimage(cv::InputArray image, QImage &out)
{
    switch(image.type())
    {
    case CV_8UC4:
    {
        cv::Mat view(image.getMat());
        QImage view2(view.data, view.cols, view.rows, view.step[0], QImage::Format_ARGB32);
        out = view2.copy();
        break;
    }
    case CV_8UC3:
    {
        cv::Mat mat;
        cvtColor(image, mat, cv::COLOR_BGR2BGRA); //COLOR_BGR2RGB doesn't behave so use RGBA
        QImage view(mat.data, mat.cols, mat.rows, mat.step[0], QImage::Format_ARGB32);
        out = view.copy();
        break;
    }
    case CV_8UC1:
    {
        cv::Mat mat;
        cvtColor(image, mat, cv::COLOR_GRAY2BGRA);
        QImage view(mat.data, mat.cols, mat.rows, mat.step[0], QImage::Format_ARGB32);
        out = view.copy();
        break;
    }
    default:
    {
        throw invalid_argument("Image format not supported");
        break;
    }
    }
}

Mat ImageConverter::qimage2mat(const QImage &qimage)
{

    cv::Mat mat = cv::Mat(qimage.height(), qimage.width(), CV_8UC4, (uchar*)qimage.bits(), qimage.bytesPerLine());
    cv::Mat mat2 = cv::Mat(mat.rows, mat.cols, CV_8UC3 );
    int from_to[] = { 0,0,  1,1,  2,2 };
    cv::mixChannels( &mat, 1, &mat2, 1, from_to, 3 );
    return mat2;

}

QImage ImageConverter::ImageToContrast(QImage &qimage, int val)
{
    double contrast;
    double colorRed, colorGreen, colorBlue;
    int pixels;
    unsigned int *data;

    contrast = (100.0+val)/100.0;
    pixels = qimage.width()*qimage.height();
    data = (unsigned int *)qimage.bits();

    for (int i = 0; i < pixels; ++i)
    {
        colorRed= 128+ contrast*(qRed(data[i])-128);
        colorRed = (colorRed < 0x00) ? 0x00 : (colorRed > 0xff) ? 0xff : colorRed;
        colorGreen= 128+ contrast*(qGreen(data[i])-128);
        colorGreen = (colorGreen < 0x00) ? 0x00 : (colorGreen > 0xff) ? 0xff : colorGreen;
        colorBlue= 128+ contrast*(qBlue(data[i])-128);
        colorBlue =  (colorBlue  < 0x00) ? 0x00 : (colorBlue  > 0xff) ? 0xff : colorBlue ;
        data[i] = qRgba(colorRed, colorGreen, colorBlue, qAlpha(data[i]));
    }
    return qimage;
}

QImage ImageConverter::ImageToBrightness(QImage &qimage, int val)
{
    double colorRed, colorGreen, colorBlue;
    int pixels;
    unsigned int *data;

    pixels = qimage.width() * qimage.height();
    data = (unsigned int *)qimage.bits();
    for (int i = 0; i < pixels; ++i)
    {
        colorRed= qRed(data[i])+ val;
        colorRed = (colorRed < 0x00) ? 0x00 : (colorRed > 0xff) ? 0xff : colorRed;
        colorGreen= qGreen(data[i])+val;
        colorGreen = (colorGreen < 0x00) ? 0x00 : (colorGreen > 0xff) ? 0xff : colorGreen;
        colorBlue= qBlue(data[i])+val;
        colorBlue =  (colorBlue  < 0x00) ? 0x00 : (colorBlue  > 0xff) ? 0xff : colorBlue ;
        data[i] = qRgba(colorRed, colorGreen, colorBlue, qAlpha(data[i]));
    }
    return qimage;
}

QImage ImageConverter::DrawContourOnImage(QImage &qimage)
{
    RNG rng(12345);
    // convert the image to grayscale format
    Mat img_gray;
    cvtColor(qimage2mat(qimage), img_gray, COLOR_BGR2GRAY);
    // apply binary thresholding
    Mat thresh;
    threshold(img_gray, thresh, 150, 255, THRESH_BINARY);
    //imshow("Binary mage", thresh);

    // detect the contours on the binary image using cv2.CHAIN_APPROX_NONE
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(thresh, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE,Point(0,0));
    // draw contours on the original image
    Mat image_copy = qimage2mat(qimage).clone();
    //imshow("Copy mage", image_copy);
    //use this function for only regular rectanle not a rotated.
    //drawContours(image_copy, contours, -1, Scalar(0, 255, 0), 2);
    //imshow("None approximation", image_copy);

    /// Find the rotated rectangles and ellipses for each contour (use this for rotated rectangle)
    vector<RotatedRect> minRect(contours.size());
    vector<RotatedRect> minEllipse(contours.size());
    for (int i = 0; i < contours.size(); i++)
    {
        minRect[i] = minAreaRect(Mat(contours[i]));
        if (contours[i].size() > 5)
        {
            minEllipse[i] = fitEllipse(Mat(contours[i]));
        }
    }

    /// Draw contours + rotated rects + ellipses
    Mat drawing = Mat::zeros(thresh.size(), CV_8UC3);

    for (int i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        // contour
        //drawContours(drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point());
        // ellipse
        //ellipse(drawing, minEllipse[i], color, 2, 8);
        // rotated rectangle
        Point2f rect_points[4]; minRect[i].points(rect_points);
        //check minimum square
        if(minRect[i].size.width>10 && minRect[i].size.width <500){
            for (int j = 0; j < 4; j++)
                line(image_copy, rect_points[j], rect_points[(j + 1) % 4], Scalar(255, 0, 0), 2, 8);
        }
    }

    //    imshow("None approximation", image_copy);
    //    waitKey(0);
    //    destroyAllWindows();
    QImage *cnvrttoQImg= new QImage();
    mat_to_qimage(image_copy,*cnvrttoQImg);
    return *cnvrttoQImg;
}

Mat ImageConverter::blob_detection(const cv::Mat &parseImg)
{
    // Setup SimpleBlobDetector parameters.
    SimpleBlobDetector::Params params;

    // Change thresholds
    params.minThreshold = 10;
    params.maxThreshold = 200;

    // Filter by Area.
    params.filterByArea = true;
    params.minArea = 1500;

    // Filter by Circularity
    params.filterByCircularity = true;
    params.minCircularity = 0.1;

    // Filter by Convexity
    params.filterByConvexity = true;
    params.minConvexity = 0.87;

    // Filter by Inertia
    params.filterByInertia = true;
    params.minInertiaRatio = 0.01;
    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

    // Read image
    Mat grayImage;
    cvtColor(parseImg, grayImage, COLOR_BGR2GRAY);

    // Set up the detector with default parameters.
    //SimpleBlobDetector detector;

    // Detect blobs.
    std::vector<KeyPoint> keypoints;
    detector->detect( grayImage, keypoints);

    // Draw detected blobs as red circles.
    // DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures the size of the circle corresponds to the size of blob
    Mat im_with_keypoints;
    drawKeypoints( grayImage, keypoints, im_with_keypoints, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );
    return  im_with_keypoints;
}

Mat ImageConverter::cannyEdgeDetection(const Mat &matImg)
{
    Mat imgOriginal;
    Mat imgGrayscale;
    Mat imgBlurred;
    Mat imgCanny;

    imgOriginal = matImg;
    cvtColor(imgOriginal, imgGrayscale, /*CV_BGR2GRAY */ COLOR_BGR2RGB);
    GaussianBlur(imgGrayscale, imgBlurred, Size(1,1), 1.5);
    Canny(imgBlurred, imgCanny, 50, 120);

    return imgCanny;

}

Mat ImageConverter::convertToLaplacian(const Mat &imgMat)
{
    Mat imgOriginal, imgGray, mat_dst;
    int kernelSize = 3, scale = 1, delta = 0, ddepth = CV_16S;

    imgOriginal = imgMat; // load/assign image value

    // Reduce noise by blurring with a Gaussian filter ( kernel size = 3 )
    GaussianBlur(imgOriginal, imgOriginal, Size(3, 3), 0, 0, BORDER_DEFAULT);
    cvtColor(imgOriginal, imgGray, COLOR_BGR2GRAY);

    Mat abs_dst;
    Laplacian(imgGray, mat_dst, ddepth, kernelSize, scale, delta, BORDER_DEFAULT);

    //converting back to CV_8U
    convertScaleAbs(mat_dst, abs_dst);

    return abs_dst;
}
