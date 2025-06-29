//
// Created by varev on 6/29/25.
//

#ifndef MOTIONDETECTOR_HPP
#define MOTIONDETECTOR_HPP
#include <opencv2/core/mat.hpp>

class MotionDetector {
public:
    MotionDetector(int thresh = 30, double minArea = 200.0);
    bool detect(const cv::Mat &frame, std::vector<cv::Rect>& motionRects);

private:
    cv::Mat m_baseline, m_current, m_diff;
    int m_threshold;
    double m_minContourArea;
    bool m_isInitialized;
};

#endif //MOTIONDETECTOR_HPP
