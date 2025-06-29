#include <iostream>
#include <thread>

#include "camera/CameraManager.hpp"
#include "recording/RecordingManager.hpp"

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

    cv::Mat baseline = camera.captureFrame();

    auto startTime = std::chrono::steady_clock::now();
    auto endTime = startTime + std::chrono::milliseconds(5050);

    bool init = true;

    const std::chrono::milliseconds frameDuration(33);
    while (true) {
        auto frameStart = std::chrono::steady_clock::now();
        cv::Mat frame = camera.captureFrame();

        bool motionDetected = init;

        if (motionDetected) {
            if (!recorder.isRecording()) {
                recorder.startRecording("motion_" + generateTimestamp() + ".avi");
            }
            recorder.writeFrame(frame);
            recorder.onMotionDetected();
            init = false;
        } else {
            if (recorder.isRecording()) {
                recorder.writeFrame(frame);
                recorder.onNoMotion();
            }
        }

        if (endTime <= std::chrono::steady_clock::now()) {
            recorder.stopRecording();
            break;
        }

        auto frameEnd = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart);
        std::cout << "Elapsed: " << elapsed.count() << "ms" << std::endl;

        if (elapsed < frameDuration) {
            std::this_thread::sleep_for(frameDuration - elapsed);
        }
    }

    return 0;
}
