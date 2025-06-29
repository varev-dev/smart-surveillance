//
// Created by varev on 6/27/25.
//
#include "camera/CameraManager.hpp"

CameraManager::CameraManager() {
    std::string pipeline = "libcamerasrc ! "
                          "video/x-raw,width=1280,height=720,format=RGB,framerate=30/1 ! "
                          "queue max-size-buffers=1 leaky=downstream ! "
                          "videoconvert ! "
                          "appsink sync=false drop=true max-buffers=1 emit-signals=true";
    m_capture = std::make_unique<cv::VideoCapture>(pipeline, cv::CAP_GSTREAMER);

    if (!m_capture->isOpened()) {
        std::cerr << "Unable to open camera" << std::endl;
        return;
    }

    m_capture->set(cv::CAP_PROP_FRAME_WIDTH, 1280);
    m_capture->set(cv::CAP_PROP_FRAME_HEIGHT, 720);

    std::cout << "Camera initialized successfully" << std::endl;
}

CameraManager::~CameraManager() {
    if (isOpened()) {
        m_capture->release();
    }
}

bool CameraManager::isOpened() const {
    return m_capture && m_capture->isOpened();
}

cv::Mat CameraManager::captureFrame() const {
    cv::Mat frame;

    if (!isOpened()) {
        std::cerr << "Capture failed: Camera not opened" << std::endl;
        return frame;
    }

    bool ret = m_capture->read(frame);
    if (!ret || frame.empty()) {
        std::cerr << "Unable to capture frame" << std::endl;
    }

    return frame;
}
