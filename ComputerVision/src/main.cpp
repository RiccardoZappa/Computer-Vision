#include <opencv2/opencv.hpp>
#include <onnxruntime_cxx_api.h>

#include "camera/cameraGrabber.hpp"

using namespace Camera;

int main() 
{
    CameraGrabber grabber{};

    auto videoCapture = grabber.getVideoCapture();
    int deviceID = 0;
    int ApiID = cv::CAP_ANY;

    videoCapture.open(deviceID, ApiID);

    cv::Mat frame;

    while(videoCapture.read(frame))
    {
        cv::imshow("RealTime detection", frame);
        if(cv::waitKey(1) == 'q') break;
    }
    auto providers = Ort::GetAvailableProviders();
    for (auto provider : providers)
    {
        std::cout << provider << std::endl;
    }
    return 0;
}