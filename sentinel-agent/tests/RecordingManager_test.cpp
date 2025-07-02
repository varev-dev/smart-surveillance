//
// Created by varev on 7/1/25.
//
#include "recording/RecordingManager.hpp"

#include <gtest/gtest.h>

TEST(RecordingManagerTest, StartRecordingSetsFlag) {
    RecordingManager recorder;
    EXPECT_FALSE(recorder.isRecording());

    recorder.startRecording("dummy.avi");
    EXPECT_TRUE(recorder.isRecording());
}

TEST(RecordingManagerTest, StopsRecordingClearsFlag) {
    RecordingManager recorder;
    recorder.startRecording("dummy.avi");
    recorder.stopRecording();

    EXPECT_FALSE(recorder.isRecording());
}

TEST(RecordingManagerTest, StartsRecordingOnMotion) {
    RecordingManager recorder;
    EXPECT_FALSE(recorder.isRecording());

    recorder.onMotionDetected();
    EXPECT_TRUE(recorder.isRecording());
}

TEST(RecordingManagerTest, StopsRecordingAfterStableFramesThreshold) {
    RecordingManager recorder;
    recorder.onMotionDetected();
    EXPECT_TRUE(recorder.isRecording());

    for (uint32_t i = 0; i < recorder.getStableFramesThreshold(); ++i)
        recorder.onNoMotion();

    EXPECT_FALSE(recorder.isRecording());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}