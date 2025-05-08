#include "sylarx/log/log.h"

namespace sylarx {

// LogLevel 实现
constexpr std::string_view LogLevelConverter::ToString(
    LogLevel level) noexcept {
    using enum LogLevel;
    switch (level) {
    case DEBUG:
        return "DEBUG";
    case INFO:
        return "INFO";
    case WARN:
        return "WARN";
    case ERROR:
        return "ERROR";
    case FATAL:
        return "FATAL";
    default:
        return "UNKNOWN";
    }
}

LogLevel LogLevelConverter::FromString(std::string_view str) {
    using enum LogLevel;
    if (str == "DEBUG")
        return DEBUG;
    if (str == "INFO")
        return INFO;
    if (str == "WARN")
        return WARN;
    if (str == "ERROR")
        return ERROR;
    if (str == "FATAL")
        return FATAL;
    if (str == "UNKNOWN")
        return UNKNOWN;
    throw std::invalid_argument("Invalid log level string");
}

LogEvent::LogEvent(std::shared_ptr<Logger> logger, LogLevel level,
                   const std::source_location& location,
                   std::chrono::milliseconds elapse, uint32_t thread_id,
                   uint32_t fiber_id,
                   std::chrono::system_clock::time_point timestamp,
                   std::string_view thread_name)
    : logger_(std::move(logger)),
      level_(level),
      location_(location),
      elapse_(elapse),
      thread_id_(thread_id),
      fiber_id_(fiber_id),
      timestamp_(timestamp),
      thread_name_(thread_name) {}

}  // namespace sylarx