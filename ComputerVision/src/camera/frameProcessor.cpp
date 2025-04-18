#include "camera/frameProcessor.hpp"

using namespace Camera;

void FrameProcessor::ProcessFrame(const cv::Mat& originalFrame, cv::Mat& processedFrame)
{
    const int target_width = 640;
    const int target_height = 640;
    const float scale_factor = 1.0f / 255.0f; // For normalization to [0.0, 1.0]
    const bool swapRB = true;

    processedFrame = cv::dnn::blobFromImage(
        originalFrame,
        scale_factor,
        cv::Size(target_width,target_height),
        cv::Scalar(0,0,0),
        swapRB,
        false,
        CV_32F
    );
}