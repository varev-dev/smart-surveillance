//
// Created by varev on 6/28/25.
//
#ifndef RECORDINGMANAGER_HPP
#define RECORDINGMANAGER_HPP
#include <atomic>
#include <opencv2/videoio.hpp>

class RecordingManager {
public:
    RecordingManager();
    ~RecordingManager();

    void startRecording(const std::string& filename = "", const cv::Size& size = cv::Size(1280, 720), const double& framerate = 24.0);
    void stopRecording();

    void setNextFilename(const std::string& filename);

    bool isRecording() const;

    void writeFrame(const cv::Mat& frame);
    void onMotionDetected();
    void onNoMotion();

    static std::string generateFilename();

#ifdef DEBUG
    uint32_t getStableFrameCount() const;
    uint32_t getStableFramesThreshold() const;
#endif

private:
    cv::VideoWriter m_writer;
    std::atomic<bool> m_isRecording{false};
    std::atomic<uint32_t> m_stableFrameCounter{0};
    std::string m_nextFilename;

    const uint32_t m_stableFramesThreshold = 48;
};

#endif //RECORDINGMANAGER_HPP
