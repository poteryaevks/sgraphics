####################################
function(_SG_INSTALL_DEPS
        PROJECT
        )


endfunction()


macro(_SG_EXPORT_TARGET
        PROJECT
        TARGET
        HEADERS
        )

    # install target
    install(TARGETS ${TARGET}
        EXPORT ${TARGET}Targets
        CONFIGURATIONS ${CMAKE_BUILD_TYPE}
        LIBRARY DESTINATION ${LIBRARY_INSTALL_DIR}
        ARCHIVE DESTINATION ${LIBRARY_INSTALL_DIR}
        INCLUDES DESTINATION ${INCLUDE_INSTALL_DIR}
        )

    # generate and install export file
    install(EXPORT ${TARGET}Targets
        FILE ${PROJECT}${TARGET}Targets.cmake
        NAMESPACE ${PROJECT}::
        DESTINATION ${CONFIG_INSTALL_DIR}
        )

    # install header files
    foreach(HEADER ${HEADERS})

        get_filename_component(filename ${HEADER} NAME)
        string(REPLACE "${SG_SOURCE_ROOT_DIR}" "" path ${HEADER})
        string(REPLACE "${filename}" "" path ${path})

        install(FILES ${HEADER}
            DESTINATION "${INCLUDE_INSTALL_DIR}/${path}"
            )

    endforeach()


endmacro()

####################################
function(_SG_ADD_LIBRARY
        PROJECT
        TARGET
        SOURCES
        HEADERS
        TYPE
        )

    if(${TYPE} STREQUAL "INTERFACE")

        add_library(${TARGET} ${TYPE}
            )

        target_include_directories(${TARGET} ${TYPE}
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
            "$<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}>"
            )

    else()

        add_library(${TARGET} ${TYPE}
            ${SOURCES}
            ${HEADERS}
            )


        set_target_properties(${TARGET} PROPERTIES
            CXX_STANDARD 14
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS NO
            PREFIX "lib${LOWER_PROJECT_NAME}_"
            )

        target_include_directories(${TARGET} PUBLIC
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
            )

    endif()

    add_library(${PROJECT}::${TARGET}
        ALIAS ${TARGET}
        )

endfunction()

####################################
function(_SG_CONFIGURE_PROJECT
        PROJECT
        )

    include(CMakePackageConfigHelpers)

    configure_package_config_file("cmake/Config.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT}Config.cmake"
        INSTALL_DESTINATION "${CONFIG_INSTALL_DIR}"
        )

    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT}ConfigVersion.cmake"
        VERSION "${version}"
        COMPATIBILITY AnyNewerVersion
        )


    install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT}ConfigVersion.cmake"
        DESTINATION ${CONFIG_INSTALL_DIR}
        )

endfunction()

# Get all propreties that cmake supports
execute_process(COMMAND cmake --help-property-list OUTPUT_VARIABLE CMAKE_PROPERTY_LIST)

# Convert command output into a CMake list
STRING(REGEX REPLACE ";" "\\\\;" CMAKE_PROPERTY_LIST "${CMAKE_PROPERTY_LIST}")
STRING(REGEX REPLACE "\n" ";" CMAKE_PROPERTY_LIST "${CMAKE_PROPERTY_LIST}")

function(print_properties)
    message ("CMAKE_PROPERTY_LIST = ${CMAKE_PROPERTY_LIST}")
endfunction(print_properties)

function(print_target_properties tgt)
    if(NOT TARGET ${tgt})
        message("There is no target named '${tgt}'")
        return()
    endif()

    foreach (prop ${CMAKE_PROPERTY_LIST})
        string(REPLACE "<CONFIG>" "${CMAKE_BUILD_TYPE}" prop ${prop})
        # Fix https://stackoverflow.com/questions/32197663/how-can-i-remove-the-the-location-property-may-not-be-read-from-target-error-i
        if(prop STREQUAL "LOCATION" OR prop MATCHES "^LOCATION_" OR prop MATCHES "_LOCATION$")
            continue()
        endif()
        # message ("Checking ${prop}")
        get_property(propval TARGET ${tgt} PROPERTY ${prop} SET)
        if (propval)
            get_target_property(propval ${tgt} ${prop})
            message ("${tgt} ${prop} = ${propval}")
        endif()
    endforeach(prop)
endfunction(print_target_properties)



