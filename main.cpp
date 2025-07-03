#include <opencv2/opencv.hpp>
#include <iostream>
#include "trainc.h"
#include "trainopen.h"
using namespace std;

int main() {
    // ����ͼ��
    string img_path = "D:/1_SLYwork/project/train/MyOpenCVProject/00005.png";
    string save_path = "D:/1_SLYwork/project/train/MyOpenCVProject/00005_gray.png";

    cv::Mat image = cv::imread(img_path); // �滻Ϊ���ͼ��·��
    if (image.empty()) {
        std::cout << "Error: Could not load the image!" << std::endl;
        return -1;
    }

    cv::Mat grayImage = convertToGray(image);
    cv::imwrite(save_path, grayImage);
   
    // ��ʾͼ��
    //cv::imshow("Test Image", grayImage);
    //cv::waitKey(0); // �ȴ�����
    //cv::destroyAllWindows();

    return 0;
}