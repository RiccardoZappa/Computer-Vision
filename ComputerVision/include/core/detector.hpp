#include <memory>
#include <onnxruntime_cxx_api.h>


namespace Core 
{
    class Detector
    {
        Detector();

    private:
        std::unique_ptr<Ort::Env> m_upOrtEnviroment;
        std::unique_ptr<Ort::SessionOptions> m_upOrtSessionOptions;
        std::unique_ptr<Ort::Session> m_upOrtSession;
    };
}