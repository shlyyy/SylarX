# 仅在启用测试时构建
option(BUILD_TESTS "Build unit tests" ON)

if(BUILD_TESTS)
    enable_testing()

    # 自动发现所有测试
    file(GLOB test_dirs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*")
    message(STATUS "Test directories: ${test_dirs}")

    foreach(test_dir ${test_dirs})
        if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${test_dir})
            file(GLOB test_sources ${test_dir}/*.cc)
            foreach(test_source ${test_sources})
                get_filename_component(test_name ${test_source} NAME_WE)
                message(STATUS "Adding test: ${test_name}")

                add_executable(${test_name} ${test_source})
                target_link_libraries(${test_name}
                    PRIVATE
                    sylarx
                    GTest::GTest
                    GTest::Main
                )
                add_test(NAME ${test_name} COMMAND ${test_name})
            endforeach()
        endif()
    endforeach()
endif()