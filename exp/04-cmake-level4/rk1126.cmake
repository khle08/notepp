
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# set(tools /home/ubt/Documents/compilation/arm-ca9-linux-gnueabihf-6.5)              # HIKVISION
set(tools /home/thomas/rv1126/repo_new/buildroot/output/rockchip_rv1126_rv1109/host)  # RV1126 / 1109

set(CMAKE_C_COMPILER ${tools}/bin/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER ${tools}/bin/arm-linux-gnueabihf-g++)


# # search for programs in the build host directories (not necessary)
# SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# # for libraries and headers in the target directories
# SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)


# !!!!! FAILED !!!!!