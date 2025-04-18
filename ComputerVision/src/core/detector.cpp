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

std::vector<Ort::Value> Detector::runInference(const Ort::RunOptions& run_options, const char* const* input_names,
     const Ort::Value* input_values, size_t input_count, const char* const* output_names, size_t output_count)
{
    try 
    {
        auto output_tensors = m_upOrtSession->Run(
            run_options,
            input_names,
            input_values,
            input_count,
            output_names,
            output_count
        );
        return output_tensors;
    }
    catch (const Ort::Exception& exception) {
        std::cerr << "ERROR running inference: " << exception.what() << std::endl;
    }
    return {};
}

void Detector::ProcessOutput(std::vector<Ort::Value> outputTensors)
{
    
}