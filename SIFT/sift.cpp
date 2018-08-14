#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

using namespace std;
using namespace cv;
using cv::xfeatures2d::SIFT;

int main(int argc, char const *argv[])
{
    const char *filename1 = (argc == 1 ? "../../pic/box_in_scene.png" : argv[1]);
    const char *filename2 = (argc == 1 ? "../../pic/box.png" : argv[2]);

    Mat img1, img2;
    img1 = imread(filename1);
    img2 = imread(filename2);

    if (img1.empty() || img2.empty())
        return -1;

    Ptr<Feature2D> sift1 = SIFT::create();
    Ptr<Feature2D> sift2 = SIFT::create();

    vector<KeyPoint> keypoints1;
    vector<KeyPoint> keypoints2;

    Mat dscriptors1;
    Mat dscriptors2;

    BFMatcher matcher(cv::NORM_L2, true);
    vector<DMatch> matches;

    Mat out_img;

    sift1->detectAndCompute(img1, Mat(), keypoints1, dscriptors1);
    sift2->detectAndCompute(img2, Mat(), keypoints2, dscriptors2);

    matcher.match(dscriptors1, dscriptors2, matches, Mat());

    // select 30 points
    nth_element(matches.begin(),
                matches.begin() + 29,
                matches.end());
    matches.erase(matches.begin() + 30, matches.end());

    drawMatches(img1, keypoints1,
                img2, keypoints2,
                matches,
                out_img,
                Scalar(255, 255, 255));

    imshow("SIFT", out_img);
    waitKey(0);

    return 0;
}
