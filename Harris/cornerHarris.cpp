#include <iostream>
#include "opencv2/opencv.hpp"
#include "cornerHarris.h"

using namespace std;
using namespace cv;

int main(int argc, char const *argv[])
{
    const char *filename = (argc == 1 ? "../../pic/building.jpg" : argv[1]);
    Mat src, src_gray;
    Mat dst, dst_norm, dst_norm_scaled;

    src = imread(filename);
    if (src.empty())
        return -1;
    cvtColor(src, src_gray, COLOR_BGR2GRAY);

    int blockSize = 2;
    int apertureSize = 3;
    double k = 0.04;
    int thresh = 155;
    cornerHarris_xx(src_gray,
                    dst,
                    blockSize,
                    apertureSize,
                    k,
                    BORDER_DEFAULT);
    normalize(dst,
              dst_norm,
              0,
              255,
              NORM_MINMAX,
              CV_32FC1,
              Mat());
    convertScaleAbs(dst_norm, dst_norm_scaled);

    for (int j = 0; j < dst_norm.rows; j++)
        for (int i = 0; i < dst_norm.cols; i++)
            if ((int)dst_norm.at<float>(j, i) > thresh)
                circle(src,
                       Point(i, j),
                       5,
                       Scalar(0, 0, 255),
                       1,
                       8,
                       0);

    imshow("Harris corners", src);
    waitKey(0);

    return 0;
}