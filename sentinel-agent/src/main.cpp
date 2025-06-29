#include <iostream>
#include <thread>

#include "camera/CameraManager.hpp"
#include "recording/RecordingManager.hpp"
#include "detection/MotionDetector.hpp"

std::string generateTimestamp() {
    const auto now = std::chrono::system_clock::now();
    const std::time_t calendar_time = std::chrono::system_clock::to_time_t(now);
    const std::tm local_tm = *std::localtime(&calendar_time);

    std::ostringstream oss;
    oss << std::put_time(&local_tm, "%Y_%m_%d-%H:%M:%S");
    return oss.str();
}

int main() {
    CameraManager camera{};
    RecordingManager recorder{};
    MotionDetector detector{};

    auto startTime = std::chrono::steady_clock::now();
    auto endTime = startTime + std::chrono::milliseconds(60050);

    std::vector<cv::Rect> boxes;

    const std::chrono::milliseconds frameDuration(33);
    const std::chrono::milliseconds waitDuration(500);
    while (true) {
        auto frameStart = std::chrono::steady_clock::now();
        cv::Mat frame = camera.captureFrame();

        bool motionDetected = detector.detect(frame, boxes);

        if (motionDetected) {
            if (!recorder.isRecording()) {
                recorder.startRecording("motion_" + generateTimestamp() + ".avi");
            }
            recorder.writeFrame(frame);
            recorder.onMotionDetected();
        } else {
            if (recorder.isRecording()) {
                recorder.writeFrame(frame);
                recorder.onNoMotion();
            }
        }

        auto frameEnd = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart);
        std::cout << "Elapsed: " << elapsed.count() << "ms" << std::endl;

        if (recorder.isRecording()) {
            std::this_thread::sleep_for(frameDuration - elapsed);
        } else {
            if (endTime <= std::chrono::steady_clock::now()) {
                break;
            }
            std::this_thread::sleep_for(waitDuration - elapsed);
        }
    }

    return 0;
}
