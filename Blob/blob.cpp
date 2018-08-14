#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char const *argv[])
{
    const char *filename = (argc == 1 ? "../../pic/box_in_scene.png" : argv[1]);
    Mat img;
    img = imread(filename);
    if (img.empty())
        return -1;

    SimpleBlobDetector::Params params;
    params.minThreshold = 40;
    params.maxThreshold = 160;
    params.thresholdStep = 5;
    params.minArea = 100;
    params.maxArea = 8000;
    params.minConvexity = .05f;
    params.minInertiaRatio = .05f;
    Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

    vector<KeyPoint> key_points;
    detector->detect(img, key_points);

    Mat out_img;
    drawKeypoints(img,
                  key_points,
                  out_img,
                  Scalar(0, 0, 255),
                  DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    namedWindow("Blob", WINDOW_AUTOSIZE);
    imshow("Blob", out_img);
    waitKey(0);

    return 0;
}
