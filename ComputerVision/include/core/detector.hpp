#include <memory>
#include <onnxruntime_cxx_api.h>


namespace Core 
{
    class Detector
    {
    public:
        Detector();
        void initialize(std::string model);

    private:
        std::unique_ptr<Ort::Env> m_upOrtEnviroment;
        std::unique_ptr<Ort::Session> m_upOrtSession;
    };
}