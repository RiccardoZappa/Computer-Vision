#pragma once
#include <opencv2/opencv.hpp>

namespace Core 
{
    class PipelineStage
    {
    public:
        virtual ~PipelineStage();

        virtual cv::Mat Process(const& cv::Mat input) = 0;

        virtual std::string getName() const = 0;
    }
}