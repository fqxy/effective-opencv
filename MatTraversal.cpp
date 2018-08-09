#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void colorReduce(Mat &, int);
void colorReducePtr(const Mat &, Mat &, int);
void colorReduceEffective(const Mat &, Mat &, int);
void colorReduceIterator(const Mat &, Mat &, int);

int main(int argc, char const *argv[])
{
    if (argc != 2)
        return -1;

    Mat src = imread(argv[1]);
    if (src.empty())
        return -1;

    imshow("src", src);
    // colorReduce(src, 40);
    // imshow("reduce_1", src);

    Mat dst;
    colorReducePtr(src, dst, 40);
    imshow("reduce_2", dst);

    Mat dst_3;
    colorReduceEffective(src, dst_3, 40);
    imshow("reduce_3", dst_3);

    Mat dst_4;
    colorReduceEffective(src, dst_4, 40);
    imshow("reduce_4", dst_4);

    waitKey(0);
    return 0;
}

// at()
void colorReduce(Mat &img, int div)
{
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            // + div/2 can increase brightness
            // <Vec3b> can reserve rgb, <unchar> can reserve gray
            img.at<Vec3b>(i, j)[0] = img.at<Vec3b>(i, j)[0] / div * div + div / 2;
            img.at<Vec3b>(i, j)[1] = img.at<Vec3b>(i, j)[1] / div * div + div / 2;
            img.at<Vec3b>(i, j)[2] = img.at<Vec3b>(i, j)[2] / div * div + div / 2;
        }
    }
}

// pointer
void colorReducePtr(const Mat &src, Mat &dst, int div)
{
    dst.create(src.size(), src.type());
    int rows = src.rows;
    int cols = src.cols;               //  -----line------
    int lines = cols * src.channels(); // [[bgr], [bgr] ... ;[bgr] ... ; ...]
    for (int i = 0; i < rows; i++)
    { // the pointer of ith row
        const uchar *srcData = src.ptr<uchar>(i);
        uchar *dstData = dst.ptr<uchar>(i);
        for (int j = 0; j < lines; j++)
            dstData[j] = srcData[j] / div * div + div / 2;
    }
}

// this method is the most effective
void colorReduceEffective(const Mat &src, Mat &dst, int div)
{
    dst.create(src.size(), src.type());
    int rows = src.rows;
    int cols = src.cols;

    if (src.isContinuous() && dst.isContinuous())
    {
        cols = cols * rows * src.channels();
        rows = 1;
    }

    for (int i = 0; i < rows; i++)
    {
        const uchar *srcData = src.ptr<uchar>(i);
        uchar *dstData = dst.ptr<uchar>(i);
        for (int j = 0; j < cols; j++)
            *dstData++ = *srcData++ / div * div + div / 2;
    }
}

// iterator
void colorReduceIterator(const Mat &src, Mat &dst, int div)
{
    dst.create(src.size(), src.type());
    MatConstIterator_<Vec3b> srcIt = src.begin<Vec3b>();
    MatConstIterator_<Vec3b> srcEnd = src.end<Vec3b>();

    MatIterator_<Vec3b> dstIt = dst.begin<Vec3b>();

    while (srcIt != srcEnd)
    {
        (*dstIt)[0] = (*srcIt)[0] / div * div + div / 2;
        (*dstIt)[1] = (*srcIt)[1] / div * div + div / 2;
        (*dstIt)[2] = (*srcIt)[2] / div * div + div / 2;
        srcIt++;
        dstIt++;
    }
}
