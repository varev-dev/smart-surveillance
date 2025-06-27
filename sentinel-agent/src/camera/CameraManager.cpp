//
// Created by varev on 6/27/25.
//
#include "camera/CameraManager.hpp"

CameraManager::CameraManager() {
    m_capture = std::make_unique<cv::VideoCapture>(0);

    if (!m_capture->isOpened()) {
        std::cerr << "Unable to open camera" << std::endl;
        return;
    }

    m_capture->set(cv::CAP_PROP_FRAME_WIDTH, 1920);
    m_capture->set(cv::CAP_PROP_FRAME_HEIGHT, 1080);

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

    *m_capture >> frame;

    if (frame.empty()) {
        std::cerr << "Unable to capture frame" << std::endl;
    }

    return frame;
}
