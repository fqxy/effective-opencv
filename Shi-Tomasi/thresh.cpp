#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char const *argv[])
{
    Mat src(Size(3, 3), CV_8UC1);
    src.at<uchar>(0, 0) = 20;
    src.at<uchar>(0, 1) = 21;
    src.at<uchar>(0, 2) = 22;
    src.at<uchar>(1, 0) = 23;
    src.at<uchar>(1, 1) = 24;
    src.at<uchar>(1, 2) = 25;
    src.at<uchar>(2, 0) = 26;
    src.at<uchar>(2, 1) = 27;
    src.at<uchar>(2, 2) = 28;
    cout << src << endl;

    threshold(src, src, 24, 0, THRESH_TOZERO);
    cout << src << endl;

    return 0;
}
