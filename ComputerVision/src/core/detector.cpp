#include "core/detector.hpp"

using namespace Core;

Detector::Detector() :
    m_upOrtEnviroment{std::make_unique<Ort::Env>(ORT_LOGGING_LEVEL_WARNING, "ObjectDetectionEnv")},
    m_upOrtSession{}
{
}

void Detector::initialize(std::string model)
{

}

