
file(GLOB USER_LIBS_FILE ./*.cpp)

add_library(UsageEnvironment 
        STATIC
        ${USER_LIBS_FILE})

add_definitions("-Wall -g")
add_definitions(${self_def})
#add_compile_options(-std=c++11 -O -DSOCKLEN_T=socklen_t -g -D_LARGEFILE_SOURCE=1 -D_FILE_OFFSET_BITS=64 -Wall -DBSD=1)

# [!] ... or linked here locally and separatedly
# target_include_directories(UsageEnvironment 
#         PUBLIC .
#         PUBLIC include
#         PUBLIC ../groupsock/include)
