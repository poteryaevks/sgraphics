include(${CMAKE_MODULES_DIR}/functions.cmake)

set(LIB_DIRECTORY ${CMAKE_SOURCE_DIR}/third_party/sdl_font_cache)
set(TARGET_NAME sdl_font_cache)

file(GLOB _SOURCE_FILES
    ${LIB_DIRECTORY}/*.c
    )

file (GLOB _HEADER_FILES
    ${LIB_DIRECTORY}/*.hpp
    ${LIB_DIRECTORY}/*.h
    )

_SG_ADD_LIBRARY(
    ${PROJECT_NAME}
    ${TARGET_NAME}
    "${_SOURCE_FILES}"
    "${_HEADER_FILES}"
    STATIC
    )

target_link_libraries(${TARGET_NAME} PUBLIC SDL2 SDL2_ttf)
target_include_directories(${TARGET_NAME} PUBLIC ${SDL2_INCLUDE_DIRS})

_SG_EXPORT_TARGET(${PROJECT_NAME}
    "${TARGET_NAME}"
    "${_HEADER_FILES}"
    )
