#include "trainopen.h"

cv::Mat convertToGray(const cv::Mat& input) {
    cv::Mat gray;
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
    return gray;
}

void Main_Opencv() {
    string img_path = "D:/1_SLYwork/project/train/MyOpenCVProject/00005.png";
    string save_path = "D:/1_SLYwork/project/train/MyOpenCVProject/00005_gray.png";

    cv::Mat image = cv::imread(img_path);
    if (image.empty()) {
        std::cout << "Error: Could not load the image!" << std::endl;
        return;
    }

    cv::Mat grayImage = convertToGray(image);
    cv::imwrite(save_path, grayImage);

    //cv::imshow("Test Image", grayImage);
    //cv::waitKey(0);
    //cv::destroyAllWindows();
}