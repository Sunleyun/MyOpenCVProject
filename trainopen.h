#ifndef TRAINOPEN_H
#define TRAINOPEN_H
#define _USE_MATH_DEFINES
#include <opencv2/opencv.hpp>
#include <cmath>
#include <vector>
#include <queue>

cv::Mat convertToGray(const cv::Mat& input);
cv::Mat gammaTransform(const cv::Mat& img, float gamma);
cv::Mat Blur_Gaussian(const cv::Mat& img, int kernal, double param);
cv::Mat Canny_Detection(const cv::Mat& img, int t1, int t2);
std::vector<float> Calc_Histogram(const cv::Mat& img);
cv::Mat Equal_Histogram(const cv::Mat& img);

cv::Mat convertToGray_Manual(const cv::Mat& img);
cv::Mat gammaTransform_Manual(const cv::Mat& img, float gamma);
std::vector<std::vector<float>> createGaussianKernal(int size, float sigma);
cv::Mat Blur_Gaussian_Manual(const cv::Mat& img, int kernal, double param);
cv::Mat Canny_Detection_Manual(const cv::Mat& img, int t1, int t2);
std::vector<float> Calc_Histogram_Manual(const cv::Mat& img);
cv::Mat Equal_Histogram_Manual(const cv::Mat& img);

cv::Mat Draw_Vector(const std::vector<float>& data, bool isLine, int height, int width);

class ImageProcessor {
public:
	ImageProcessor(const std::string&);
	double getAverageBrightness() const;
private:
	cv::Mat img;
};

void Main_Opencv();

#endif // TRAINOPEN_H