# 查找GTest
find_package(GTest REQUIRED)

# 创建测试可执行文件
add_executable(test_logger
    test_logger.cc
)

# 链接库和GTest
target_link_libraries(test_logger
    PRIVATE
        sylarx_log
        GTest::GTest
        GTest::Main
)

# 添加测试
add_test(NAME logger_test COMMAND test_logger)