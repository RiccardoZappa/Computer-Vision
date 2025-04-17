#include "camera/cameraGrabber.hpp"

using namespace Camera;

CameraGrabber::CameraGrabber() :
    m_videoCapture{}
{
}

cv::VideoCapture CameraGrabber::getVideoCapture()
{
    return m_videoCapture;
}
