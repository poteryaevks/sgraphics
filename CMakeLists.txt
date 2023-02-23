cmake_minimum_required(VERSION 3.11.0)

project(SG LANGUAGES C CXX VERSION 0.1)

set(CMAKE_MODULES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(${CMAKE_MODULES_DIR}/functions.cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

# Config

if(EXISTS "${CMAKE_SOURCE_DIR}/LocalConfig.cmake")
    include("${CMAKE_SOURCE_DIR}/LocalConfig.cmake")
else()
    message(FATAL_ERROR "LocalConfig.cmake has not been found. Please, put it into project root directory.")
endif()

find_package(Boost 1.62 REQUIRED COMPONENTS
    program_options
    system
    )
    
if(NOT alm_FOUND)

    if(EXISTS ${ALM_ROOT})
        list(APPEND CMAKE_PREFIX_PATH "${ALM_ROOT}/lib/cmake/alm")
    endif()

    find_package(alm CONFIG
        COMPONENTS
        vimpel
        misc
        config
        math
        prot_decl
        router
        logger
        REQUIRED
        )

endif()

link_directories(${CMAKE_CURRENT_BINARY_DIR})

find_package(GLEW REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

if(${GLEW_FOUND})
    message("GLEW version: " ${GLEW_VERSION})
    message("GLEW libs: " ${GLEW_LIBRARIES})
    message("GLEW include: " ${GLEW_INCLUDE_DIRS})
endif()

if(${SDL2_FOUND})
    message("SLD2 version: " ${SDL2_VERSION})
    message("SLD2 libs: " ${SDL2_LIBRARIES})
    message("SLD2 include: " ${SDL2_INCLUDE_DIRS})
endif()

set(CMAKE_DEBUG_POSTFIX "d")

set(SG_SOURCE_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(SG_BINARY_ROOT_DIR "${CMAKE_CURRENT_BINARY_DIR}")

string(TOLOWER ${PROJECT_NAME} LOWER_PROJECT_NAME)

set(CONFIG_INSTALL_DIR lib/cmake/${LOWER_PROJECT_NAME})
set(INCLUDE_INSTALL_DIR include)
set(LIBRARY_INSTALL_DIR lib)

include_directories(${CMAKE_SOURCE_DIR})

if(USE_THIRD_PARTY)
    add_subdirectory(third_party/sdl_font_cache)
endif()

add_subdirectory(sgraphics/geometry)
add_subdirectory(sgraphics/convertion)
add_subdirectory(sgraphics/engine)

if(BUILD_TESTING)
    enable_testing()
    find_package(GTest REQUIRED)
    add_subdirectory(tests)
endif()

_SG_CONFIGURE_PROJECT(${PROJECT_NAME})
