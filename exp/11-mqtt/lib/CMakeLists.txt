
# add_library(pahoMqtt SHARED IMPORTED)

# # If versions are setup, 3 libs will be generated:
# # libcalibration.1.0.so / libcalibration.1.so / libcalibration.so
# set_target_properties(pahoMqtt PROPERTIES
#     # VERSION 1.0 SOVERSION 1
#     IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/paho/libpaho-mqtt3c.so
#     # IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/paho/libpaho-mqtt3c.so
#     PUBLIC_HEADER ${CMAKE_SOURCE_DIR}/lib/paho/include/MQTTAsync.h
#     PUBLIC_HEADER ${CMAKE_SOURCE_DIR}/lib/paho/include/MQTTClient.h
#     PUBLIC_HEADER ${CMAKE_SOURCE_DIR}/lib/paho/include/MQTTClientPersistence.h
#     PUBLIC_HEADER ${CMAKE_SOURCE_DIR}/lib/paho/include/MQTTExportDeclarations.h
#     PUBLIC_HEADER ${CMAKE_SOURCE_DIR}/lib/paho/include/MQTTProperties.h
#     PUBLIC_HEADER ${CMAKE_SOURCE_DIR}/lib/paho/include/MQTTReasonCodes.h
#     PUBLIC_HEADER ${CMAKE_SOURCE_DIR}/lib/paho/include/MQTTSubscribeOpts.h
# )


add_library(mqtt SHARED mqtt.cpp)
target_link_libraries(mqtt PRIVATE
                      ${CMAKE_THREAD_LIBS_INIT}
                      ${PAHO_LIBS}
                      # pahoMqtt
                      )

set_target_properties(mqtt PROPERTIES VERSION 1.0 SOVERSION 1)
# If versions are setup, 3 libs will be generated:
# libcalibration.1.0.so / libcalibration.1.so / libcalibration.so

install(TARGETS mqtt
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(FILES mqtt.h DESTINATION include)

