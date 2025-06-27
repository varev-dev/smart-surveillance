#include <iostream>

#include "camera/CameraManager.hpp"

int main() {
    CameraManager manager{};

    if (!manager.isOpened()) {
        std::cerr << "Failed to open camera" << std::endl;
    }

    const cv::Mat frame = manager.captureFrame();

    if (frame.empty()) {
        return -1;
    }

    if (const std::string filename = "image.jpg"; cv::imwrite(filename, frame)) {
        std::cout << "Image saved to " << filename << std::endl;
    } else {
        std::cerr << "Failed to save image to " << filename << std::endl;
    }

    return 0;
}
