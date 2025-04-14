#include <opencv2/opencv.hpp>

int main() {
    cv::Mat materis;
    materis = cv::imread("data/sample.jpg", cv::IMREAD_COLOR );
    return 0;
}