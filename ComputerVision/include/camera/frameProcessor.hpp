#include <opencv2/opencv.hpp>

namespace Camera 
{
    class FrameProcessor
    {
    public:
        static void ProcessFrame(const cv::Mat& originalFrame, cv::Mat& processedFrame);
    };
}