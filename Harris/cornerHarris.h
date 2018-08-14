#include <opencv2/opencv.hpp>

using namespace cv;

enum
{
    MINEIGENVAL = 0,
    HARRIS = 1,
    EIGENVALSVECS = 2
};

static void calcHarris_xx(const Mat &_cov, Mat &_dst, double k)
{
    int i, j;
    Size size = _cov.size();

    if (_cov.isContinuous() && _dst.isContinuous())
        size.width *= size.height;
    size.height = 1;

    for (i = 0; i < size.height; i++)
    {
        const float *cov = _cov.ptr<float>(i);
        float *dst = _dst.ptr<float>(i);

        for (j = 0; j < size.width; j++)
        {
            float a = cov[j * 3];
            float b = cov[j * 3 + 1];
            float c = cov[j * 3 + 2];
            dst[j] = float(a * c - b * b - k * (a + c) * (a + c));
        }
    }
}

void cornerEigenValsVecs_xx(const Mat &src,
                            Mat &eigenv,
                            int block_size,
                            int aperture_size,
                            int op_type,
                            double k = 0.,
                            int borderType = BORDER_DEFAULT)
{
    int depth = src.depth();
    double scale = (double)(1 << ((aperture_size > 0 ? aperture_size : 3) - 1)) * block_size;
    if (aperture_size < 0)
        scale *= 2.;
    if (depth == CV_8U)
        scale *= 255.;
    scale = 1. / scale;

    CV_Assert(src.type() == CV_8UC1 || src.type() == CV_32FC1);

    // 1.计算图像I在水平方向和垂直方向的梯度
    Mat Dx, Dy;
    if (aperture_size > 0)
    {
        Sobel(src, Dx, CV_32F, 1, 0, aperture_size, scale, 0, borderType);
        Sobel(src, Dy, CV_32F, 0, 1, aperture_size, scale, 0, borderType);
    }
    else
    {
        Scharr(src, Dx, CV_32F, 1, 0, scale, 0, borderType);
        Scharr(src, Dy, CV_32F, 0, 1, scale, 0, borderType);
    }

    // 2.计算两个方向梯度的乘积
    Size size = src.size();
    Mat cov(size, CV_32FC3);
    int i, j;
    for (i = 0; i < size.height; i++)
    {
        float *cov_data = cov.ptr<float>(i);
        float *dxdata = Dx.ptr<float>(i);
        float *dydata = Dy.ptr<float>(i);
        for (j = 0; j < size.width; j++)
        {
            float dx = dxdata[j];
            float dy = dydata[i];

            cov_data[j * 3] = dx * dx;
            cov_data[j * 3 + 1] = dx * dy;
            cov_data[j * 3 + 2] = dy * dy;
        }
    }

    // 3.加权处理，得到自相关矩阵(采用方框滤波)
    boxFilter(cov,
              cov,
              cov.depth(),
              Size(block_size, block_size),
              Point(-1, -1),
              false,
              borderType);

    if (op_type == HARRIS)
        calcHarris_xx(cov, eigenv, k);
}

void cornerHarris_xx(InputArray _src,
                     OutputArray _dst,
                     int blockSize,
                     int ksize,
                     double k,
                     int borderType)
{
    Mat src = _src.getMat();
    _dst.create(src.size(), CV_32FC1);
    Mat dst = _dst.getMat();

    // 4.求R
    cornerEigenValsVecs_xx(src, dst, blockSize, ksize, HARRIS, k, borderType);
}
