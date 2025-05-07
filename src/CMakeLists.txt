# 主库配置
add_library(sylarx)

# 自动包含所有模块
file(GLOB modules RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*")
message(STATUS "Modules: ${modules}")

foreach(module ${modules})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${module})
        # 添加模块源文件
        file(GLOB sources ${module}/*.cc)
        message(STATUS "Module: ${module} Sources: ${sources}")

        target_sources(sylarx PRIVATE ${sources})

        # 将 include 目录暴露给了所有链接该库的目标
        target_include_directories(sylarx PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
            $<INSTALL_INTERFACE:include>
        )
    endif()
endforeach()


# 安装到 CMAKE_INSTALL_PREFIX/lib 和 bin
install(TARGETS sylarx
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
# 安装头文件到 CMAKE_INSTALL_PREFIX/include
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/sylarx DESTINATION include)