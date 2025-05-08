#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include "sylarx/log/log.h"

using namespace sylarx;

void basic_usage() {
    auto logger = std::make_shared<sylarx::Logger>();
    auto event =
        std::make_shared<sylarx::LogEvent>(logger, sylarx::LogLevel::INFO);

    // 1. 直接输出字符串
    event->format("This is a simple message");
    std::cout << event->content() << std::endl;

    // 2. 使用位置参数
    event->format("User {} logged in from {}", "Alice", "192.168.1.100");
    std::cout << event->content() << std::endl;

    // 3. 格式化数字
    event->format("The result is {:.2f}",
                  3.1415926);  // 输出: The result is 3.14
    std::cout << event->content() << std::endl;

    // 4. 对齐和填充
    event->format("{:<10}|{:^10}|{:>10}", "left", "center", "right");
    std::cout << event->content() << std::endl;

    // 5. 混合类型
    event->format("ID: {:05d}, Name: {}, Active: {}", 42, "Bob", true);
    std::cout << event->content() << std::endl;
}

int main() {
    basic_usage();

    std::cout << "\n=== All tests completed ===\n";
    return 0;
}