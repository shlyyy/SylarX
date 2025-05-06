cmake_minimum_required(VERSION 3.22)
project(SylarX LANGUAGES CXX)

# 基础设置
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找GTest
find_package(GTest REQUIRED)

# 启用测试
enable_testing()



# 添加子目录
# add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(tests)
# add_subdirectory(examples)