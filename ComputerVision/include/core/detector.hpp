#include <memory>
#include <onnxruntime_cxx_api.h>


namespace Core 
{
    class Detector
    {
    public:
        Detector();
        void initialize(const wchar_t* model);

        std::vector<Ort::Value> runInference(const Ort::RunOptions& run_options, const char* const* input_names, const Ort::Value* input_values, size_t input_count,
            const char* const* output_names, size_t output_count);

        void ProcessOutput(std::vector<Ort::Value> outputTensors);
    private:
        std::unique_ptr<Ort::Env> m_upOrtEnviroment;
        std::unique_ptr<Ort::Session> m_upOrtSession;
    };
}