//
// Created by varev on 6/28/25.
//
#include "recording/RecordingManager.hpp"

RecordingManager::RecordingManager() {}

RecordingManager::~RecordingManager() {}

void RecordingManager::startRecording(const std::string& filename) {
    m_writer.open(filename, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30.0, cv::Size(1280, 720));
    m_isRecording = true;
    m_stableFrameCounter = 0;
}

void RecordingManager::stopRecording() {
    m_isRecording = false;
    m_stableFrameCounter = 0;
    m_writer.release();
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
    m_stableFrameCounter = 0;
}

void RecordingManager::onNoMotion() {
    ++m_stableFrameCounter;

    if (m_stableFrameCounter >= m_stableFramesThreshold) {
        stopRecording();
    }
}
