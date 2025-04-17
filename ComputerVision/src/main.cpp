#include <opencv2/opencv.hpp>
#include <onnxruntime_cxx_api.h>


int main() {
    cv::Mat materis;
    materis = cv::imread("data/sample.jpg", cv::IMREAD_COLOR );
    auto providers = Ort::GetAvailableProviders();
    for (auto provider : providers)
    {
        std::cout << provider << std::endl;
    }
    return 0;
}