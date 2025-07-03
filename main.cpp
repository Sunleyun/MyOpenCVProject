#include <opencv2/opencv.hpp>
#include <iostream>
#include "trainc.h"
#include "trainopen.h"
using namespace std;

int main() {
    // 加载图像
    string img_path = "D:/1_SLYwork/project/train/MyOpenCVProject/00005.png";
    string save_path = "D:/1_SLYwork/project/train/MyOpenCVProject/00005_gray.png";

    cv::Mat image = cv::imread(img_path); // 替换为你的图像路径
    if (image.empty()) {
        std::cout << "Error: Could not load the image!" << std::endl;
        return -1;
    }

    cv::Mat grayImage = convertToGray(image);
    cv::imwrite(save_path, grayImage);
   
    // 显示图像
    //cv::imshow("Test Image", grayImage);
    //cv::waitKey(0); // 等待按键
    //cv::destroyAllWindows();

    return 0;
}