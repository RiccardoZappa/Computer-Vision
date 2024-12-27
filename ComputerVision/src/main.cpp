#include "core/PipelineManager.hpp"
#include "stages/EdgeDetectionStage.hpp"
#include <opencv2/opencv.hpp>

using namespace Core;
using namespace Stages;

int main() {
    PipelineManager manager;
    manager.addStage(std::make_shared<EdgeDetectionStage>());

    cv::Mat image = cv::imread("C:/Computer-Vision/ComputerVision/data/sample.jpg", cv::IMREAD_GRAYSCALE);
    cv::Mat result = manager.run(image);

    cv::imshow("Result", result);
    cv::waitKey(0);
    std::cout << "passed from here";
    return 0;
}