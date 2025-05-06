add_library(sylarx_log
    log.cc
)

target_include_directories(sylarx_log
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

# 安装规则（可选）
install(TARGETS sylarx_log DESTINATION lib)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/sylarx
        DESTINATION include
)