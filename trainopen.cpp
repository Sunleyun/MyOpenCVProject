#include "trainopen.h"
using namespace std;

cv::Mat convertToGray(const cv::Mat& input) {
    cv::Mat gray;
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
    return gray;
}

cv::Mat convertToGray_Manual(const cv::Mat& img) {
    if (img.empty() || img.channels() != 3 || img.type() != CV_8UC3) {
        return cv::Mat();
    }

    int height = img.rows;
    int width = img.cols;

    cv::Mat gray(height, width, CV_8UC1);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cv::Vec3b pixel = img.at<cv::Vec3b>(i, j);
            uchar b = pixel[0];
            uchar g = pixel[1];
            uchar r = pixel[2];

            // ptr<uchar> Consider continuous storage and discontinuous storage respectively
            // const uchar* inputData = img.ptr<uchar>(0);
            // uchar* outputData = gray.ptr<uchar>(0);
            // uchar b = inputData[i * 3];

            // gray = 0.299 * R + 0.587 * G + 0.114 * B
            float grayValue = 0.299 * r + 0.587 * g + 0.114 * b;
            
            int result = static_cast<int>(grayValue + 0.5f);
            if (result > 255) result = 255;
            if (result < 0) result = 0;

            gray.at<uchar>(i, j) = static_cast<uchar>(result);
        }
    }
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

cv::Mat gammaTransform_Manual(const cv::Mat& img, float gamma) {
    if (img.empty() || img.channels() != 1 || img.type() != CV_8UC1 || gamma <= 0) {
        return cv::Mat();
    }

    int height = img.rows;
    int width = img.cols;

    cv::Mat result(height, width, CV_8UC1);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float pixel = img.at<uchar>(i, j) / 255.0;
            float transformed = pow(pixel, gamma);
            int value = static_cast<int>(transformed * 255.0f + 0.5f);
            result.at<uchar>(i, j) = min(255, max(0, value));
        }
    }
    return result;
}

cv::Mat Blur_Gaussian(const cv::Mat& img, int kernal=5, double param=1.0) {
    cv::Mat result;
    cv::GaussianBlur(img, result, cv::Size(kernal, kernal), param);
    return result;
}

vector<vector<float>> createGaussianKernal(int size, float sigma) {
    vector<vector<float>> kernal(size, vector<float>(size));
    float sum = 0.0f;
    int half = size / 2;

    for (int i = -half; i <= half; ++i) {
        for (int j = -half; j <= half; ++j) {
            float value = exp(-(i * i + j * j) / (2 * sigma * sigma));
            kernal[i + half][j + half] = value;
            sum += value;
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            kernal[i][j] /= sum;
        }
    }

    return kernal;
}

cv::Mat Blur_Gaussian_Manual(const cv::Mat& img, int kernal, double param) {
    //G(x,y)=(1/2*pi*sigma^2)exp(-(x^2+y^2)/(2*sigma^2))
    if (img.empty() || img.type() != CV_8UC1 || kernal % 2 == 0 || param <= 0) {
        return cv::Mat();
    }

    vector<vector<float>> kernel = createGaussianKernal(kernal, param);
    int half = kernal / 2;

    cv::Mat result(img.size(), CV_8UC1);
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            float sum = 0.0f;
            for (int m = -half; m <= half; m++) {
                for (int n = -half; n <= half; n++) {
                    int x = i + m;
                    int y = j + n;
                    if (x >= 0 && x < img.rows && y >= 0 && y < img.cols) {
                        sum += kernel[m + half][n + half] * img.at<uchar>(x, y);
                    }
                }
            }
            int value = static_cast<int>(sum + 0.5f);
            result.at<uchar>(i, j) = min(255, max(0, value));
        }
    }
    return result;
}

cv::Mat Canny_Detection(const cv::Mat& img, int t1=50, int t2=150) {
    cv::Mat result;
    cv::Canny(img, result, t1, t2);
    return result;
}

cv::Mat Canny_Detection_Manual(const cv::Mat& img, int t1=50, int t2=150) {
    if (img.empty() || img.type() != CV_8UC1 || t1 < 0 || t2 < t1) {
        return cv::Mat();
    }

    int rows = img.rows;
    int cols = img.cols;

    //gradient sobel
    cv::Mat grad_magnitude(rows, cols, CV_32FC1);
    cv::Mat grad_direction(rows, cols, CV_32FC1);
    for (int i = 1; i < rows-1; i++) {
        for (int j = 1; j < cols - 1; j++) {
            int gx = (-img.at<uchar>(i - 1, j - 1) + img.at<uchar>(i - 1, j + 1)
                - 2 * img.at<uchar>(i, j - 1) + 2 * img.at<uchar>(i, j + 1)
                - img.at<uchar>(i + 1, j - 1) + img.at<uchar>(i + 1, j + 1));
            int gy = (-img.at<uchar>(i - 1, j - 1) + img.at<uchar>(i + 1, j - 1)
                - 2 * img.at<uchar>(i - 1, j) + 2 * img.at<uchar>(i + 1, j)
                - img.at<uchar>(i - 1, j + 1) + img.at<uchar>(i + 1, j + 1));
            grad_magnitude.at<float>(i, j) = sqrt(gx * gx + gy * gy);
            grad_direction.at<float>(i, j) = atan2(gy, gx);
        }
    }

    //Non-maximum suppression
    cv::Mat suppressed(rows, cols, CV_8UC1, cv::Scalar(0));
    for (int i = 1; i < rows - 1; i++) {
        for (int j = 1; j < cols - 1; j++) {
            float mag = grad_magnitude.at<float>(i, j);
            float angle = grad_direction.at<float>(i, j) * 180.0 / M_PI;
            //0/45/90/135
            int dir;
            if ((angle >= -22.5 && angle < 22.5) || angle >= 157.5 || angle < -157.5)
                dir = 0;
            else if ((angle >= 22.5 && angle < 67.5) || angle >= -157.5 || angle < -112.5)
                dir = 45;
            else if ((angle >= -67.5 && angle < 112.5) || angle >= -112.5 || angle < -67.5)
                dir = 90;
            else dir = 135;

            float mag1 = 0, mag2 = 0;
            if (dir == 0) {
                mag1 = grad_magnitude.at<float>(i, j - 1);
                mag2 = grad_magnitude.at<float>(i, j + 1);
            }
            else if(dir == 45) {
                mag1 = grad_magnitude.at<float>(i - 1, j + 1);
                mag2 = grad_magnitude.at<float>(i + 1, j - 1);
            }
            else if (dir == 90) {
                mag1 = grad_magnitude.at<float>(i - 1, j);
                mag2 = grad_magnitude.at<float>(i + 1, j);
            }
            else {
                mag1 = grad_magnitude.at<float>(i - 1, j - 1);
                mag2 = grad_magnitude.at<float>(i + 1, j + 1);
            }

            if (mag >= mag1 && mag >= mag2) {
                suppressed.at<uchar>(i, j) = static_cast<uchar>(min(255.0f, mag));
            }
        }
    }

    //Double threshold
    cv::Mat edges(rows, cols, CV_8UC1, cv::Scalar(0));
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    queue<pair<int, int>> strong_edges;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            uchar mag = suppressed.at<uchar>(i, j);
            if (mag > t2) {
                edges.at<uchar>(i, j) = 255;
                strong_edges.push({i, j});
                visited[i][j] = true;
            }
            else if (mag > t1) {
                edges.at<uchar>(i, j) = 128;
            }
        }
    }

    //Edge tracking
    int di[8] = { -1, -1, -1, 0, 0, 1, 1, 1};
    int dj[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    while (!strong_edges.empty()) {
        int i, j;
        tie(i, j) = strong_edges.front();
        strong_edges.pop();
        for (int k = 0; k < 8; k++) {
            int ni = i + di[k];
            int nj = j + dj[k];
            if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && !visited[ni][nj]) {
                if (edges.at<uchar>(ni, nj) == 128) {
                    edges.at<uchar>(ni, nj) = 255;
                    strong_edges.push({ ni, nj });
                    visited[ni][nj] = true;
                }
            }
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (edges.at<uchar>(i, j) != 255)
                edges.at<uchar>(i, j) = 0;
        }
    }

    return edges;
}

vector<float> Calc_Histogram(const cv::Mat& img) {
    if (img.empty() || img.type() != CV_8UC1) {
        return vector<float>();
    }

    int histSize = 256;
    float range[] = { 0, 256 };
    const float* histRange = { range };
    cv::Mat hist;

    cv::calcHist(&img, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, true, false);

    vector<float> histogram(256);
    float totalPixels = img.rows * img.cols;
    for (int i = 0; i < 256; i++) {
        histogram[i] = hist.at<float>(i) / totalPixels;
    }

    return histogram;
}

vector<float> Calc_Histogram_Manual(const cv::Mat& img) {
    if (img.empty() || img.type() != CV_8UC1) {
        return vector<float>();
    }

    vector<float> histogram(256, 0.0f);
    int totalPixels = img.rows * img.cols;

    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            uchar pixel = img.at<uchar>(i, j);
            histogram[pixel]++;
        }
    }

    for (float& value : histogram) {
        value /= totalPixels;
    }

    return histogram;
}

cv::Mat Equal_Histogram(const cv::Mat& img) {
    if (img.empty() || img.type() != CV_8UC1) {
        return cv::Mat();
    }

    cv::Mat result;
    cv::equalizeHist(img, result);
    return result;
}

cv::Mat Equal_Histogram_Manual(const cv::Mat& img) {
    if (img.empty() || img.type() != CV_8UC1) {
        return cv::Mat();
    }

    vector<float> histogram(256, 0.0f);
    int totalPixels = img.rows * img.cols;

    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            uchar pixel = img.at<uchar>(i, j);
            histogram[pixel]++;
        }
    }

    //calculate CDF
    vector<float> cdf(256, 0.0f);
    cdf[0] = histogram[0];
    for (int i = 1; i < 256; i++) {
        cdf[i] = cdf[i - 1] + histogram[i];
    }

    float cdfMin = cdf[0];
    for (int i = 1; i < 256; i++) {
        if (cdf[i] > 0 && (cdfMin == 0 || cdf[i] < cdfMin)) {
            cdfMin = cdf[i];
        }
    }

    vector<uchar> lut(256);
    for (int i = 0; i < 256; i++) {
        if (cdf[i] > 0) {
            lut[i] = static_cast<uchar>(std::min(255.0f, (cdf[i] - cdfMin) / (totalPixels - cdfMin) * 255.0f + 0.5f));
        }
        else {
            lut[i] = 0;
        }
    }

    cv::Mat result(img.size(), CV_8UC1);
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            result.at<uchar>(i, j) = lut[img.at<uchar>(i, j)];
        }
    }

    return result;
}

cv::Mat Draw_Vector(const std::vector<float>& data, bool isLine = true, int height = 400, int width = 800) {
    if (data.empty()) return cv::Mat();
    cv::Mat image(height, width, CV_8UC3, cv::Scalar(255, 255, 255));

    float maxVal = 0;
    for (float val : data) {
        if (val > maxVal) maxVal = val;
    }
    if (maxVal == 0) maxVal = 1;

    int size = data.size();
    float binWidth = static_cast<float>(width) / size;

    if (isLine) {
        for (int i = 0; i < size - 1; i++) {
            cv::Point p1(static_cast<int>(i * binWidth), height - static_cast<int>(data[i] / maxVal * (height - 20)));
            cv::Point p2(static_cast<int>(i + 1) * binWidth, height - static_cast<int>(data[i + 1] / maxVal * (height - 20)));
            cv::line(image, p1, p2, cv::Scalar(0, 0, 255), 1);
        }
    }
    else {
        for (int i = 0; i < size; i++) {
            int h = static_cast<int>(data[i] / maxVal * (height - 20));
            cv::rectangle(image,
                cv::Point(static_cast<int>(i * binWidth), height),
                cv::Point(static_cast<int>((i + 1) * binWidth), height - h),
                cv::Scalar(0, 0, 255),
                cv::FILLED);
        }
    }
    return image;
}

ImageProcessor::ImageProcessor(const string& path) {
    img = cv::imread(path, cv::IMREAD_GRAYSCALE);
}

double ImageProcessor::getAverageBrightness() const {
    return cv::mean(img)[0];
}

void Main_Opencv() {
    string img_path = "D:/1_SLYwork/project/train/MyOpenCVProject/00005.png";
    string save_path = "D:/1_SLYwork/project/train/MyOpenCVProject/00005_Hist.png";
    string save_path_l = "D:/1_SLYwork/project/train/MyOpenCVProject/00005_Hist_l.png";
    string save_path_b = "D:/1_SLYwork/project/train/MyOpenCVProject/00005_Hist_b.png";

    cv::Mat image = cv::imread(img_path);
    if (image.empty()) {
        std::cout << "Error: Could not load the image!" << std::endl;
        return;
    }

    cv::Mat grayImage = convertToGray(image);
    cv::Mat equalhist = Equal_Histogram_Manual(grayImage);
    vector<float> hist = Calc_Histogram_Manual(grayImage);

    cv::Mat linePlot = Draw_Vector(hist, true);
    cv::Mat barPlot = Draw_Vector(hist, false);

    cv::imwrite(save_path, equalhist);
    cv::imwrite(save_path_l, linePlot);
    cv::imwrite(save_path_b, barPlot);

    //cv::Mat grayImage = convertToGray(image);
    //cv::Mat blur_image = Blur_Gaussian(image, 3, 1.0);
    //blur_image = Canny_Detection(blur_image, 50, 150);
    //cv::imwrite(save_path, blur_image);

    //cv::imshow("Test Image", grayImage);
    //cv::waitKey(0);
    //cv::destroyAllWindows();
}