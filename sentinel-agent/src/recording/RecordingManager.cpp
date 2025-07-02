//
// Created by varev on 6/28/25.
//
#include "recording/RecordingManager.hpp"
#include "utils/TimeUtils.hpp"
#include <spdlog/spdlog.h>

RecordingManager::RecordingManager() {}

RecordingManager::~RecordingManager() {}

void RecordingManager::startRecording(const std::string& filename, const cv::Size& size, const double& framerate) {
    std::string recordingFilename;
    if (!filename.empty()) {
        recordingFilename = filename;
    } else if (!m_nextFilename.empty()) {
        recordingFilename = m_nextFilename;
        m_nextFilename.clear();
    } else {
        recordingFilename = generateFilename();
    }

    m_writer.open(recordingFilename, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), framerate, size);
    m_isRecording = true;
    m_stableFrameCounter = 0;
    spdlog::info("Recording {} started.", recordingFilename);
}

void RecordingManager::stopRecording() {
    m_isRecording = false;
    m_stableFrameCounter = 0;
    m_writer.release();
    spdlog::info("Recording stopped.");
}

void RecordingManager::setNextFilename(const std::string &filename) {
    m_nextFilename = filename;
}

std::string RecordingManager::generateFilename() {
    return "motion_" + TimeUtils::generateTimestamp() + ".avi";
}

bool RecordingManager::isRecording() const {
    return m_isRecording;
}

void RecordingManager::writeFrame(const cv::Mat &frame) {
    if (!m_isRecording) {
        return;
    }

    m_writer.write(frame);
}

void RecordingManager::onMotionDetected() {
    if (!m_isRecording) {
        startRecording();
    }

    m_stableFrameCounter = 0;
}

void RecordingManager::onNoMotion() {
    ++m_stableFrameCounter;

    if (m_stableFrameCounter >= m_stableFramesThreshold) {
        stopRecording();
    }
}

#ifdef DEBUG
uint32_t RecordingManager::getStableFrameCount() const {
    return m_stableFrameCounter;
}

uint32_t RecordingManager::getStableFramesThreshold() const {
    return m_stableFramesThreshold;
}
#endif