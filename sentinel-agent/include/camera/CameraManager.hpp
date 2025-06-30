//
// Created by varev on 6/27/25.
//

#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H
#include <memory>
#include <opencv2/opencv.hpp>

class CameraManager {
public:
    explicit CameraManager(const cv::Size& resolution = cv::Size(1280, 720), const int8_t& framerate = 24);
    ~CameraManager();

    bool isOpened() const;

    cv::Mat captureFrame() const;

private:
    std::unique_ptr<cv::VideoCapture> m_capture;
};

#endif //CAMERAMANAGER_H
