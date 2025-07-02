//
// Created by varev on 7/2/25.
//
#include "utils/TimeUtils.hpp"

#include <chrono>
#include <iomanip>
#include <sstream>

std::string TimeUtils::generateTimestamp() {
    const auto now = std::chrono::system_clock::now();
    const std::time_t calendar_time = std::chrono::system_clock::to_time_t(now);
    const std::tm local_tm = *std::localtime(&calendar_time);

    std::ostringstream oss;
    oss << std::put_time(&local_tm, "%Y_%m_%d-%H:%M:%S");
    return oss.str();
}
