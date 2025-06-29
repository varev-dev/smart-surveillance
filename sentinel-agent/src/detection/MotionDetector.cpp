//
// Created by varev on 6/29/25.
//
#include "detection/MotionDetector.hpp"

#include <opencv2/imgproc.hpp>

MotionDetector::MotionDetector(int thresh, double minArea)
    : m_threshold(thresh), m_minContourArea(minArea), m_isInitialized(false){
}

bool MotionDetector::detect(const cv::Mat &frame, std::vector<cv::Rect>& motionRects) {
    motionRects.clear();

    cv::cvtColor(frame, m_current, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(m_current, m_current, cv::Size(21, 21), 0);

    if (!m_isInitialized) {
        m_baseline = m_current.clone();
        m_isInitialized = true;
        return false;
    }

    cv::absdiff(m_baseline, m_current, m_diff);

    cv::threshold(m_diff, m_diff, m_threshold, 255, cv::THRESH_BINARY);

    const cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));
    cv::morphologyEx(m_diff, m_diff, cv::MORPH_OPEN, kernel);

    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(m_diff, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    bool motionDetected = false;
    for (const auto& contour : contours) {
        double area = cv::contourArea(contour);

        if (area > m_minContourArea) {
            motionRects.push_back(cv::boundingRect(contour));
            motionDetected = true;
        }
    }

    m_baseline = m_current.clone();

    return motionDetected;
}
