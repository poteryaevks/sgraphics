include(${CMAKE_MODULES_DIR}/functions.cmake)

set(TARGET_NAME engine)


file(GLOB _SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/impl/*.cpp
    )

file (GLOB _HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    )

_SG_ADD_LIBRARY(
    ${PROJECT_NAME}
    ${TARGET_NAME}
    "${_SOURCE_FILES}"
    "${_HEADER_FILES}"
    STATIC
    )

target_include_directories(${TARGET_NAME} PRIVATE 
    "${SG_SOURCE_ROOT_DIR}"
    )

target_compile_features(${TARGET_NAME} PUBLIC cxx_std_20)

target_link_libraries(${TARGET_NAME} PUBLIC
    GLEW
    SDL2
    SDL2_image
    )

if(USE_THIRD_PARTY)
    target_link_libraries(${TARGET_NAME} PUBLIC FontCache)
endif()

# _SG_EXPORT_TARGET(${PROJECT_NAME}
#     "${TARGET_NAME}"
#     "${_HEADER_FILES}"
#     )
