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

void Main_Opencv() {
    string img_path = "D:/1_SLYwork/project/train/MyOpenCVProject/00005.png";
    string save_path = "D:/1_SLYwork/project/train/MyOpenCVProject/00005_gamma_05.png";

    cv::Mat image = cv::imread(img_path);
    if (image.empty()) {
        std::cout << "Error: Could not load the image!" << std::endl;
        return;
    }

    cv::Mat grayImage = convertToGray(image);
    grayImage = gammaTransform(grayImage, 05);
    cv::imwrite(save_path, grayImage);

    //cv::imshow("Test Image", grayImage);
    //cv::waitKey(0);
    //cv::destroyAllWindows();
}