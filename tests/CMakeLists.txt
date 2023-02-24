cmake_minimum_required(VERSION 2.8.12)


file(GLOB _SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    )

file (GLOB _HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    )

set(TARGET_NAME sgraphics_test)

add_executable(${TARGET_NAME}
    "${_SOURCE_FILES}"
    "${_HEADER_FILES}"
    )

target_link_libraries(${TARGET_NAME}
    PRIVATE ${GTEST_LIBRARIES}
    convertion
    geometry
    engine
    )

# Includes

target_include_directories(${TARGET_NAME}
    PRIVATE ${GTEST_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}
    )

target_compile_options(${TARGET_NAME} PRIVATE
    "$<$<CONFIG:Debug>:-Wall;-D_DEBUG>"
    "$<$<CONFIG:Release>:-O2;-DNDEBUG>"
    )

set_target_properties(${TARGET_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    )
