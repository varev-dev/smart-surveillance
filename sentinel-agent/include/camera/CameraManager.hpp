//
// Created by varev on 6/27/25.
//

#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H
#include <memory>
#include <opencv2/opencv.hpp>

class CameraManager {
public:
    CameraManager();
    ~CameraManager();

    bool isOpened() const;

    cv::Mat captureFrame() const;

private:
    std::unique_ptr<cv::VideoCapture> m_capture;
};

#endif //CAMERAMANAGER_H
