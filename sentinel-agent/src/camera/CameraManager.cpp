//
// Created by varev on 6/27/25.
//
#include "camera/CameraManager.hpp"

#include <spdlog/spdlog.h>

CameraManager::CameraManager(const cv::Size& resolution, const int8_t& framerate) {
    std::string pipeline = "libcamerasrc ! "
                          "video/x-raw,width=" + std::to_string(resolution.width) +
                          ",height=" + std::to_string(resolution.height) + ",format=RGB"
                          ",framerate="+ std::to_string(framerate) + "/1 ! "
                          "queue max-size-buffers=1 leaky=downstream ! "
                          "videoconvert ! "
                          "appsink sync=false drop=true max-buffers=1 emit-signals=true";
    m_capture = std::make_unique<cv::VideoCapture>(pipeline, cv::CAP_GSTREAMER);

    if (!m_capture->isOpened()) {
        spdlog::error("Failed to open camera capture device.");
        return;
    }

    m_capture->set(cv::CAP_PROP_FPS, framerate);
    m_capture->set(cv::CAP_PROP_FRAME_WIDTH, resolution.width);
    m_capture->set(cv::CAP_PROP_FRAME_HEIGHT, resolution.height);

    spdlog::info("Successfully opened camera capture device.");
    spdlog::info("Camera Config: Resolution: {}x{}, Framerate: {} fps", resolution.width, resolution.height, framerate);
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
        spdlog::error("Failed to capture frame - camera not opened.");
        return frame;
    }

    bool ret = m_capture->read(frame);
    if (!ret || frame.empty()) {
        spdlog::error("Unable to capture frame.");
    }

    return frame;
}
