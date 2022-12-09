include(${CMAKE_MODULES_DIR}/functions.cmake)

set(TARGET_NAME convertion)


file(GLOB _SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    )

file (GLOB _HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    )

_SG_ADD_LIBRARY(
    ${PROJECT_NAME}
    ${TARGET_NAME}
    "${_SOURCE_FILES}"
    "${_HEADER_FILES}"
    STATIC
    )

target_include_directories(${TARGET_NAME}
    PRIVATE "${SG_SOURCE_ROOT_DIR}"
#     "${SG_DEPS_INCLUDE}"
    )

# target_include_directories(${TARGET_NAME} PUBLIC
#     "C:\\Program Files (x86)\\glew\\include"
#     "C:\\Program Files (x86)\\SDL2\\include"
#     )

#target_include_directories(${TARGET_NAME} INTERFACE
#    "C:\\Program Files (x86)\\glew\\include"
#    "C:\\Program Files (x86)\\SDL2\\include"
#    )

target_link_libraries(${TARGET_NAME} PRIVATE
    GLEW
    SDL2
    SDL2_image
#     "${CMAKE_INSTALL_PREFIX}/${LIBRARY_INSTALL_DIR}/libSDL2_image.dll"
    )


# target_link_libraries(${TARGET_NAME} PRIVATE
#     "${SG_DEPS_LIB_DIR}/libSDL2_image.dll"
#     )

_SG_EXPORT_TARGET(${PROJECT_NAME}
    "${TARGET_NAME}"
    "${_HEADER_FILES}"
    )
