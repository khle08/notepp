
# file(GLOB Eigen_directory_files "Eigen/*")

# foreach(f ${Eigen_directory_files})
# 	if(NOT f MATCHES "\\.txt" AND NOT f MATCHES "${ESCAPED_CMAKE_CURRENT_SOURCE_DIR}/[.].+" AND NOT f MATCHES "${ESCAPED_CMAKE_CURRENT_SOURCE_DIR}/src")
# 		list(APPEND Eigen_directory_files_to_install ${f})
# 	endif()
# endforeach(f ${Eigen_directory_files})

# install(FILES ${Eigen_directory_files_to_install}
# 		DESTINATION lib/Eigen COMPONENT Devel)


add_library(munkres SHARED munkres.cpp)
set_target_properties(munkres PROPERTIES VERSION 1.0 SOVERSION 1)

install(TARGETS munkres
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
install(FILES munkres.h matrix.h DESTINATION include)

