# 设置要求的CMake最低版本
cmake_minimum_required (VERSION 3.0)

# 设置项目名称
project (main)

# 设置系统名称为Linux
set(CMAKE_SYSTEM_NAME Linux)

# 设置系统处理器为arm
set(CMAKE_SYSTEM_PROCESSOR arm)

# 设置工具链路径
set(tools luckfox-pico-s/tools/linux/toolchain/arm-rockchip830-linux-uclibcgnueabihf/)

# 设置C编译器路径
set(CMAKE_C_COMPILER ${tools}bin/arm-rockchip830-linux-uclibcgnueabihf-gcc)

# 设置根路径
SET(CMAKE_FIND_ROOT_PATH "${tools}")

# 设置查找程序的根路径模式
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# 设置查找库的根路径模式
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)

# 设置查找包含文件的根路径模式
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# 包含目录
include_directories(lib/include)
include_directories(.)
# 设置LVGL_DIR变量
set(LVGL_DIR ${CMAKE_SOURCE_DIR}/lvgl/)

# 递归查找头文件并存储到HEADER_FILES变量中
file(GLOB_RECURSE HEADER_FILES
    "${LVGL_DIR}/*.h"
)

# 包含CMAKE_SOURCE_DIR目录
include_directories(${CMAKE_SOURCE_DIR})

# 包含LVGL_DIR目录
include_directories(${LVGL_DIR})

# 创建生成目录
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR})

# 设置输出路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# 在lib/src目录下查找源文件并存储到DIR_LIB_SRCS变量中
aux_source_directory(./lib/src DIR_LIB_SRCS)

# 在当前目录下查找源文件并存储到DIR_SRCS变量中
aux_source_directory(. DIR_SRCS)

# 递归查找LVGL/src目录下的源文件并存储到LVGL_SRC变量中
file(GLOB_RECURSE LVGL_SRC "./lvgl/src/*.c")

aux_source_directory(./lvgl lv)
# 创建名为lib_src的库并添加DIR_LIB_SRCS中的源文件
add_library (lib_src ${DIR_LIB_SRCS})

# 创建名为lvgl_src的库并添加LVGL_SRC中的源文件
add_library (lvgl_src ${LVGL_SRC})

add_library(lvgl_lv ${lv})

# 创建名为main的可执行文件并添加main.c和DIR_SRCS中的源文件
add_executable(main
    main.c ${DIR_SRCS}
)

# 将lib_src和lvgl_src库链接到main可执行文件
target_link_libraries(lvgl_lv lib_src lvgl_src)
target_link_libraries(main lib_src lvgl_src lvgl_lv)
