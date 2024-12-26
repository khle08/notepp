
cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project("expZLMHttp" LANGUAGES C CXX VERSION 1.0.0)

# cmakelists 设置c++17
set(CMAKE_CXX_STANDARD 11)

# Setup where the compiled libraries will be installed
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

option(ENABLE_ASAN "Enable Address Sanitize" OFF)
option(ENABLE_CXX_API "Enable C++ API SDK" OFF)
option(ENABLE_MEM_DEBUG "Enable Memory Debug" OFF)
option(ENABLE_MYSQL "Enable MySQL" OFF)
option(ENABLE_OPENSSL "Enable OpenSSL" ON)
option(ENABLE_WEPOLL "Enable wepoll" OFF)

option(USE_SOLUTION_FOLDERS "Enable solution dir supported" ON)

##############################################################################

# 方便修改全局变量
function(update_cached name value)
    set("${name}" "${value}" CACHE INTERNAL "*** Internal ***" FORCE)
endfunction()

function(update_cached_list name)
    set(_tmp_list "${${name}}")
    list(APPEND _tmp_list "${ARGN}")
    list(REMOVE_DUPLICATES _tmp_list)
    update_cached(${name} "${_tmp_list}")
endfunction()

# TODO:
function(set_file_group prefix)
    message(STATUS "set_file_group " ${prefix} " " ${ARGC})
    foreach(FILE IN LISTS ARGN 1)
        # Get the directory of the source file
        get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)

        # Remove common directory prefix to make the group
        string(REPLACE "${prefix}" "" GROUP "${PARENT_DIR}")

        # Make sure we are using windows slashes
        string(REPLACE "/" "\\" GROUP "${GROUP}")

        source_group("${GROUP}" FILES "${FILE}")
    endforeach()
endfunction()

##############################################################################

# mediakit 以及各个 runtime 依赖
update_cached_list(MK_LINK_LIBRARIES "")
# update_cached_list(MK_COMPILE_DEFINITIONS ENABLE_VERSION)

# include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/lib/ZLToolKit/src)
# link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/ZLToolKit/src)
# include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/lib)
# link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_subdirectory(lib)

##############################################################################

list(APPEND SOURCE
    main.cpp
)

add_executable(exe ${SOURCE})

target_link_libraries(exe PRIVATE
                      ${MK_LINK_LIBRARIES}
                      )
