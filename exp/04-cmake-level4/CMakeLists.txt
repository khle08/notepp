cmake_minimum_required(VERSION "3.10.0")

project(justAName VERSION 1.0.0)

SET(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

add_subdirectory(lib)
add_subdirectory(src)


# cmake_minimum_required
# project
# set
# file
# message
# option
# find_package

# ${CMAKE_SOURCE_DIR}
# ${PROJECT_SOURCE_DIR}
# ${PROJECT_BINARY_DIR}

# include_directories           # 添加头文件目录

# link_directories

# update_cached_list

# target_include_directories
# target_link_libraries

# set_target_properties

# add_subdirectory
# add_library                   # 添加相关的 .so 库
# add_executable