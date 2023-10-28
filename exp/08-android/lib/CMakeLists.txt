
add_library(sdk SHARED 
            CheckRuntime.cpp
            CheckRuntime.hpp
            # CreateGLBuffer.cpp
            # CreateGLBuffer.hpp
            # CreateGLContext.cpp
            CreateUserBuffer.cpp
            CreateUserBuffer.hpp
            LoadContainer.cpp
            LoadContainer.hpp
            LoadInputTensor.cpp
            LoadInputTensor.hpp
            LoadUDOPackage.cpp
            LoadUDOPackage.hpp
            NV21Load.cpp
            NV21Load.hpp
            PreprocessInput.cpp
            PreprocessInput.hpp
            SaveOutputTensor.cpp
            SaveOutputTensor.hpp
            SetBuilderOptions.cpp
            SetBuilderOptions.hpp
            Util.cpp
            Util.hpp)
target_link_libraries(sdk PRIVATE
                      ${CMAKE_THREAD_LIBS_INIT}
                      ${EXTRA_LIBS}
                      EGL
                      GLESv2
                      )


add_library(snpe SHARED IMPORTED)
set_target_properties(snpe PROPERTIES
    VERSION 1.0 SOVERSION 1
    IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/hik/bsp/libhal_bsp.so
    PUBLIC_HEADER ${CMAKE_SOURCE_DIR}/lib/hik/include/hal_barometer.h
    PUBLIC_HEADER ${CMAKE_SOURCE_DIR}/lib/hik/include/hal_esensor.h
    PUBLIC_HEADER ${CMAKE_SOURCE_DIR}/lib/hik/include/hal_hikio.h
    PUBLIC_HEADER ${CMAKE_SOURCE_DIR}/lib/hik/include/hwif_sensor.h
)


set_target_properties(snpe PROPERTIES VERSION 1.0 SOVERSION 1)
# If versions are setup, 3 libs will be generated:
# libcalibration.1.0.so / libcalibration.1.so / libcalibration.so


