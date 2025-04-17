#include <opencv2/opencv.hpp>

namespace Camera
{
    class CameraGrabber
    {
    public:
        CameraGrabber();

        cv::VideoCapture getVideoCapture();
    private:
        cv::VideoCapture m_videoCapture;
    };
}