
file(GLOB MediaKit_SRC_LIST
  ${CMAKE_CURRENT_SOURCE_DIR}/*/*.c
  ${CMAKE_CURRENT_SOURCE_DIR}/*/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/*/*.h)

if(USE_SOLUTION_FOLDERS AND (NOT GROUP_BY_EXPLORER))
  # 在 IDE 中对文件进行分组, 源文件和头文件分开
  set_file_group("${CMAKE_CURRENT_SOURCE_DIR}" ${MediaKit_SRC_LIST})
endif()

# 添加库
add_library(zlmediakit STATIC ${MediaKit_SRC_LIST})
add_library(ZLMediaKit::MediaKit ALIAS zlmediakit)

set(LINK_LIBRARIES ${MK_LINK_LIBRARIES})
list(REMOVE_ITEM LINK_LIBRARIES ZLMediaKit::MediaKit)
set(COMPILE_DEFINITIONS ${MK_COMPILE_DEFINITIONS})

target_compile_definitions(zlmediakit
  PUBLIC ${COMPILE_DEFINITIONS})
target_compile_options(zlmediakit
  PRIVATE ${COMPILE_OPTIONS_DEFAULT})
target_link_libraries(zlmediakit
  PUBLIC ${LINK_LIBRARIES})
target_include_directories(zlmediakit
  PRIVATE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
  PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>")

update_cached_list(MK_LINK_LIBRARIES ZLMediaKit::MediaKit)

# 未在使用
if(ENABLE_CXX_API)
  # 保留目录结构
  install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION ${INSTALL_PATH_INCLUDE}/ZLMediaKit
    REGEX ".*[.](md|cpp)$" EXCLUDE)
  install(TARGETS zlmediakit
    DESTINATION ${INSTALL_PATH_LIB})
endif ()
