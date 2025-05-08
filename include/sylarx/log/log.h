#ifndef __SYLARX_LOG_H__
#define __SYLARX_LOG_H__

#include <atomic>
#include <chrono>
// #include <format>
#include <fmt/args.h>
#include <fmt/compile.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/xchar.h>

#include <cstdarg>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <source_location>
#include <sstream>
#include <string>
#include <vector>

namespace sylarx {

enum class LogLevel : uint8_t {
    UNKNOWN = 0,
    DEBUG = 1,
    INFO = 2,
    WARN = 3,
    ERROR = 4,
    FATAL = 5
};

// 日志级别
class LogLevelConverter {
public:
    static constexpr std::string_view ToString(LogLevel level) noexcept;
    static LogLevel FromString(std::string_view str);
};

class Logger;

class LogEvent {
public:
    using ptr = std::shared_ptr<LogEvent>;

    LogEvent(
        std::shared_ptr<Logger> logger, LogLevel level,
        const std::source_location& location = std::source_location::current(),
        std::chrono::milliseconds elapse = std::chrono::milliseconds(0),
        uint32_t thread_id = 0, uint32_t fiber_id = 0,
        std::chrono::system_clock::time_point timestamp =
            std::chrono::system_clock::now(),
        std::string_view thread_name = "");

    // 访问器方法
    [[nodiscard]] constexpr std::string_view file() const noexcept {
        return location_.file_name();
    }

    [[nodiscard]] constexpr uint_least32_t line() const noexcept {
        return location_.line();
    }

    [[nodiscard]] std::chrono::milliseconds elapse() const noexcept {
        return elapse_;
    }

    [[nodiscard]] uint32_t thread_id() const noexcept { return thread_id_; }

    [[nodiscard]] uint32_t fiber_id() const noexcept { return fiber_id_; }

    [[nodiscard]] std::chrono::system_clock::time_point timestamp()
        const noexcept {
        return timestamp_;
    }

    [[nodiscard]] std::string_view thread_name() const noexcept {
        return thread_name_;
    }

    [[nodiscard]] std::string content() const {
        std::lock_guard lock(mutex_);
        return ss_.str();
    }

    [[nodiscard]] std::shared_ptr<Logger> logger() const noexcept {
        return logger_;
    }

    [[nodiscard]] LogLevel level() const noexcept { return level_; }

    // 获取字符串流（线程安全）
    std::stringstream& stream() noexcept { return ss_; };

    // C风格可变参数格式化
    // void format(const char* fmt, ...) {
    //     std::lock_guard<std::mutex> lock(m_mutex);
    //     va_list args;
    //     va_start(args, fmt);
    //     char* buf = nullptr;
    //     int length = vasprintf(&buf, fmt, args);
    //     if (length >= 0) {
    //         m_ss << std::string_view(buf, length);
    //         free(buf);
    //     }
    //     va_end(args);
    // }

    // 已包含va_list的版本
    // void format(const char* fmt, va_list args) {
    //     std::lock_guard<std::mutex> lock(m_mutex);
    //     char* buf = nullptr;
    //     int length = vasprintf(&buf, fmt, args);
    //     if (length >= 0) {
    //         m_ss << std::string_view(buf, length);
    //         free(buf);
    //     }
    // }

    // 替代 format_to 的实现
    // template <typename... Args>
    // void format(fmt::format_string<Args...> fmt, Args&&... args) {
    //     std::lock_guard<std::mutex> lock(m_mutex);
    //     m_ss << fmt::format(fmt, std::forward<Args>(args)...);
    // }

    // 现代C++模板格式化
    template <typename... Args>
    void format(fmt::format_string<Args...> fmt, Args&&... args) {
        std::lock_guard<std::mutex> lock(mutex_);
        fmt::format_to(std::ostream_iterator<char>(ss_), fmt,
                       std::forward<Args>(args)...);
    }

private:
    std::shared_ptr<Logger> logger_;
    LogLevel level_;
    std::source_location location_;
    std::chrono::milliseconds elapse_;
    uint32_t thread_id_;
    uint32_t fiber_id_;
    std::chrono::system_clock::time_point timestamp_;
    std::string thread_name_;
    std::stringstream ss_;
    mutable std::mutex mutex_;
};

class Logger {};
}  // namespace sylarx

#endif  // __SYLARX_LOG_H__