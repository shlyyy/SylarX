#include <gtest/gtest.h>

#include <sstream>

#include "sylarx/log/log.h"

// 测试say_hello函数
TEST(LoggerTest, SayHelloTest) {
  sylarx::say_hello();

  // 重定向cout以捕获输出
  std::stringstream buffer;
  std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

  // 调用函数
  sylarx::say_hello();

  // 恢复cout
  std::cout.rdbuf(old);

  // 验证输出
  EXPECT_EQ(buffer.str(), "Hello, world!\n");
}

// 主函数由GTest自动提供