
add_library(imgReader SHARED imgReader.cpp)
target_link_libraries(imgReader PRIVATE
                      ${CMAKE_THREAD_LIBS_INIT}
                      ${EXTRA_LIBS}
                      opencv_calib3d
                      opencv_core
                      # opencv_features2d
                      # opencv_flann
                      opencv_gapi
                      opencv_highgui
                      # opencv_img_hash
                      opencv_imgcodecs
                      # opencv_optflow
                      opencv_photo
                      opencv_video
                      opencv_videoio
                      # opencv_videostab
                      # opencv_xfeatures2d
                      # opencv_ximgproc)
                      )

set_target_properties(imgReader PROPERTIES VERSION 1.0 SOVERSION 1)
# If versions are setup, 3 libs will be generated:
# libcalibration.1.0.so / libcalibration.1.so / libcalibration.so

install(TARGETS imgReader
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(FILES imgReader.h DESTINATION include)

