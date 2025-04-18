#include <opencv2/opencv.hpp>
#include <onnxruntime_cxx_api.h>

#include "camera/cameraGrabber.hpp"
#include "camera/frameProcessor.hpp"

using namespace Camera;

int main() 
{
    CameraGrabber grabber{};

    auto videoCapture = grabber.getVideoCapture();
    int deviceID = 0;
    int ApiID = cv::CAP_ANY;

    videoCapture.open(deviceID, ApiID);

    cv::Mat frame;

    const int target_width = 640;
    const int target_height = 640;
    const float scale_factor = 1.0f / 255.0f; // For normalization to [0.0, 1.0]
    const bool swapRB = true;

    while(videoCapture.read(frame))
    {
        cv::Mat blob;

        FrameProcessor::ProcessFrame(frame, blob);

        // --- 4. Verify Blob Shape and Type (Optional) ---
        // Note: blob.size is a special object. Access dimensions via blob.size[index]
        std::cout << "Blob Info:" << std::endl;
        std::cout << "  Dimensions: " << blob.dims << std::endl; // Should be 4
        std::cout << "  Shape: [" << blob.size[0] << ", " << blob.size[1] << ", "
                  << blob.size[2] << ", " << blob.size[3] << "]" << std::endl; // Should be [1, 3, 640, 640]
        std::cout << "  Type: " << blob.type() << " (CV_32F=" << CV_32F << ")" << std::endl; // Should be 5 (CV_32F)
        std::cout << "  Total elements: " << blob.total() << std::endl; // 1*3*640*640 = 1228800
        std::cout << "  Is continuous: " << std::boolalpha << blob.isContinuous() << std::endl;

        cv::imshow("RealTime detection", frame);
        if(cv::waitKey(1) == 'q') break;
    }
    videoCapture.release();
    cv::destroyAllWindows();
    return 0;
}