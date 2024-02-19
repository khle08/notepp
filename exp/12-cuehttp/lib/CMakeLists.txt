
# 还未整理

# add_library(mqtt SHARED mqtt.cpp)
# target_link_libraries(mqtt PRIVATE
#                       ${CMAKE_THREAD_LIBS_INIT}
#                       ${PAHO_LIBS}
#                       # pahoMqtt
#                       )

# set_target_properties(mqtt PROPERTIES VERSION 1.0 SOVERSION 1)
# # If versions are setup, 3 libs will be generated:
# # libcalibration.1.0.so / libcalibration.1.so / libcalibration.so

# install(TARGETS mqtt
#         LIBRARY DESTINATION lib
#         ARCHIVE DESTINATION lib)
# install(FILES mqtt.h DESTINATION include)

