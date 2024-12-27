#pragma once
#include "core/PipelineStage.hpp"

namespace Stages 
{
    class EdgeDetectionStage : public Core::PipelineStage {
    public:  
        cv::Mat Process(const cv::Mat& input) override;

        std::string getName() const override;
    };
}