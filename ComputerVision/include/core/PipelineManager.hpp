#pragma once
#include <vector>
#include <memory>
#include "core/PipelineStage.hpp"

namespace Core
{
    class PipelineManager
    {
    public:
        void addStage(std::shared_ptr<PipelineStage> stage);

        cv::Mat run(const cv::Mat& input);
    private:
        std::vector<std::shared_ptr<PipelineStage>> m_Stages;
    };
}