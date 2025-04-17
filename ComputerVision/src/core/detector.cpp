#include <iostream>
#include "core/detector.hpp"

using namespace Core;

Detector::Detector() :
    m_upOrtEnviroment{std::make_unique<Ort::Env>(ORT_LOGGING_LEVEL_WARNING, "ObjectDetectionEnv")},
    m_upOrtSession{}
{
}

void Detector::initialize(const wchar_t* model)
{
    try
    {
        Ort::SessionOptions sessionOptions{};
        m_upOrtSession = std::make_unique<Ort::Session>(*m_upOrtEnviroment.get(), model, sessionOptions);
    }
    catch(const Ort::Exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

