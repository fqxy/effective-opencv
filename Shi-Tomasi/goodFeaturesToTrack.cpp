#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat src, src_gray;

vector<Point2f> corners;
int maxCorners = 150;
double qualityLevel = 0.01;
double minDistance = 10;
int blockSize = 3;
bool useHarrisDetector = false;
double k = 0.04;

void on_goodFeaturesToTrack(int, void *);

int main(int argc, char const *argv[])
{
    const char *filename = (argc == 1 ? "../../pic/building.jpg" : argv[1]);

    src = imread(filename);
    if (src.empty())
        return -1;
    cvtColor(src, src_gray, COLOR_BGR2GRAY);

    namedWindow("Shi-Tomashi", WINDOW_AUTOSIZE);
    createTrackbar("thresh",
                   "Shi-Tomashi",
                   &maxCorners,
                   255,
                   on_goodFeaturesToTrack);
    on_goodFeaturesToTrack(maxCorners, 0);

    waitKey(0);

    return 0;
}

void on_goodFeaturesToTrack(int, void *)
{
    Mat copy = src.clone();
    goodFeaturesToTrack(src_gray,
                        corners,
                        maxCorners,
                        qualityLevel,
                        minDistance,
                        Mat(),
                        blockSize,
                        useHarrisDetector,
                        k);
    for (int i = 0; i < corners.size(); i++)
    {
        circle(copy,
               corners[i],
               5,
               Scalar(0, 0, 255),
               -1,
               8,
               0);
    }
    imshow("Shi-Tomashi", copy);
}

#if 0
Mat image;
Mat imageGray;
int thresh = 5; //角点个数控制
int MaxThresh = 255;

void Trackbar(int, void *);

int main()
{
    image = imread("../../building.jpg");
    cvtColor(image, imageGray, CV_RGB2GRAY);
    GaussianBlur(imageGray, imageGray, Size(5, 5), 1); //滤波
    namedWindow("Corner Detected");
    createTrackbar("threshold: ", "Corner Detected", &thresh, MaxThresh, Trackbar);
    imshow("Corner Detected", image);
    Trackbar(0, 0);
    waitKey();
    return 0;
}

void Trackbar(int, void *)
{
    Mat dst, imageSource;
    dst = Mat::zeros(image.size(), CV_32FC1);
    imageSource = image.clone();
    vector<Point2f> corners;
    goodFeaturesToTrack(imageGray, corners, thresh, 0.01, 10, Mat());
    for (int i = 0; i < corners.size(); i++)
    {
        circle(imageSource, corners[i], 2, Scalar(0, 0, 255), 2);
    }
    imshow("Corner Detected", imageSource);
}
#endif