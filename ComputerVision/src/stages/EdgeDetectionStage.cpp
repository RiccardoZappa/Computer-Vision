#include "stages/EdgeDetectionStage.hpp"

using namespace Stages;

cv::Mat EdgeDetectionStage::Process(const cv::Mat& input)
 {
    cv::Mat edges;
    cv::Canny(input, edges, 50, 150);
    return edges;
}

std::string EdgeDetectionStage::getName() const
{
    return "EdgeDetection";
}