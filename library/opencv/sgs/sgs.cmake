
SET(PLATFORM sgssdk)
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_PROCESSOR aarch64)  # 或其他架构

# 确保类型大小定义正确
# SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64")  # 如果是64位目标

SET(CMAKE_C_COMPILER   /home/ubt/Documents/compilation/aj/compiler-sigmastar/bin/arm-sigmastar-linux-uclibcgnueabihf-gcc)
SET(CMAKE_CXX_COMPILER /home/ubt/Documents/compilation/aj/compiler-sigmastar/bin/arm-sigmastar-linux-uclibcgnueabihf-g++)
SET(CMAKE_STRIP        /home/ubt/Documents/compilation/aj/compiler-sigmastar/bin/arm-sigmastar-linux-uclibcgnueabihf-strip)
SET(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
