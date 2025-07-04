#include "trainopen.h"

cv::Mat convertToGray(const cv::Mat& input) {
    cv::Mat gray;
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
    return gray;
}

cv::Mat gammaTransform(const cv::Mat& img, float gamma) {
    cv::Mat result;
    img.convertTo(result, -1, 1, 0);
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            result.at<uchar>(i, j) = cv::saturate_cast<uchar>(pow(img.at < uchar>(i, j) / 255.0, gamma) * 255.0);
        }
    }
    return result;
}

cv::Mat Blur_Gaussian(const cv::Mat& img, int kernal, double param) {
    cv::Mat result;
    cv::GaussianBlur(img, result, cv::Size(kernal, kernal), param);
    return result;
}

void Main_Opencv() {
    string img_path = "D:/1_SLYwork/project/train/MyOpenCVProject/00005.png";
    string save_path = "D:/1_SLYwork/project/train/MyOpenCVProject/00005_gaussian_blur.png";

    cv::Mat image = cv::imread(img_path);
    if (image.empty()) {
        std::cout << "Error: Could not load the image!" << std::endl;
        return;
    }

    //cv::Mat grayImage = convertToGray(image);
    cv::Mat blur_image = Blur_Gaussian(image, 5, 1.0);
    cv::imwrite(save_path, blur_image);

    //cv::imshow("Test Image", grayImage);
    //cv::waitKey(0);
    //cv::destroyAllWindows();
}