#include "core/PipelineManager.hpp"

using namespace Core;

void PipelineManager::addStage(std::shared_ptr<PipelineStage> stage)
{
    m_Stages.push_back(stage);
}

cv::Mat PipelineManager::run(const cv::Mat& input)
{
    auto current = input;
    for(const auto& stage : m_Stages)
    {
        current = stage->Process(current);
    }
    return current;
}