#ifndef TRAINOPEN_H
#define TRAINOPEN_H
#include <opencv2/opencv.hpp>
using namespace std;

cv::Mat convertToGray(const cv::Mat& input);
cv::Mat gammaTransform(const cv::Mat& img, float gamma);
cv::Mat Blur_Gaussian(const cv::Mat& img, int kernal, double param);

void Main_Opencv();

#endif // TRAINOPEN_H