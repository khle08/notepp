cmake_minimum_required(VERSION 3.12)
project(Live555 LANGUAGES C CXX VERSION 1.0.0)

set(self_def0 "-std=c++11 -O0 -DSOCKLEN_T=socklen_t -g -D_LARGEFILE_SOURCE=1 -D_FILE_OFFSET_BITS=64 -Wall -DBSD=1 -DNO_STD_LIB=1")
set(self_def  "-std=c++11 -O  -DSOCKLEN_T=socklen_t -g -D_LARGEFILE_SOURCE=1 -D_FILE_OFFSET_BITS=64 -Wall -DBSD=1 -DNO_STD_LIB=1")

# [!] The header files can be either linked here globally ...
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/BasicUsageEnvironment/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/UsageEnvironment/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/groupsock/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/liveMedia/include)

add_subdirectory(BasicUsageEnvironment)
add_subdirectory(UsageEnvironment)
add_subdirectory(groupsock)
add_subdirectory(liveMedia)

file(GLOB USER_LIBS_FILE ./mediaServer/*.cpp)
add_executable(live555MediaServer ${USER_LIBS_FILE})   

add_definitions(${self_def0})

target_link_libraries(live555MediaServer
        PRIVATE liveMedia
        PRIVATE groupsock
        PRIVATE BasicUsageEnvironment
        PRIVATE UsageEnvironment
      )

# [!] ... or linked here locally and separatedly
# target_include_directories(live555MediaServer 
#         PUBLIC .
#         PUBLIC include
#         PUBLIC UsageEnvironment/include
#         PUBLIC groupsock/include
#         PUBLIC liveMedia/include
#         PUBLIC BasicUsageEnvironment/include)

