cmake_minimum_required (VERSION 3.0)
project (main)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(tools luckfox-pico-s/tools/linux/toolchain/arm-rockchip830-linux-uclibcgnueabihf/)
set(CMAKE_C_COMPILER ${tools}bin/arm-rockchip830-linux-uclibcgnueabihf-gcc)
SET(CMAKE_FIND_ROOT_PATH "${tools}")
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

include_directories(lib/include)
include_directories(.)
# 创建生成目录
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR})

# 设置输出路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

aux_source_directory(./lib/src DIR_LIB_SRCS)
aux_source_directory(. DIR_SRCS)
add_library (lib_src ${DIR_LIB_SRCS})

add_executable(main
    main.c ${DIR_SRCS}
)
target_link_libraries(main lib_src)