cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(DbNodes VERSION 1.0.0 LANGUAGES CXX)

# ====================================================================
# DEFINES
# ====================================================================
set(INI_FILE dbnodes.ini)
set(APP_ICON_MACOSX dbnodes.icns)
set(RESOURCES_FILE_NAME res.qrc)

set(DEV_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/dev-scripts)

set(DEV_SCRIPTS
        "${DEV_SCRIPTS}/install-resources.py\;${RESOURCES_FILE_NAME}\;content")

set(MACOS_DEV_SCRIPTS
#        "iconutil\;-c\;icns\;${CMAKE_CURRENT_SOURCE_DIR}/dbnodes.iconset"
    )

set(INCLUDE_DIRECTORIES
        src/Abstract
        src/Nodes
        src/Widgets
        src/Relations
        src/Modals
        src/Settings
        src/Dictionaries
        src/Saving
        src/Utils)

set(RESOURCES
        main.cpp
        src/helper.cpp
        src/helper.h)

set(INCLUDE_PROJECT_LIBS
        Widgets)

set(INI_CONFIG dbnodes.ini)

# ==================================================================
# CONFIGURE CMAKE
# ==================================================================
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-sized-deallocation -Wall")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(APP_DEBUG true)
else()
    set(APP_DEBUG false)
endif()

configure_file(config.h.in config.h @ONLY)

# ====================================================================
# EXECUTE DEV SCRIPTS
# ====================================================================

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    foreach(SCRIPT IN LISTS MACOS_DEV_SCRIPTS)
        execute_process(COMMAND ${SCRIPT})
    endforeach()
endif()

foreach(SCRIPT IN LISTS DEV_SCRIPTS)
    execute_process(COMMAND ${SCRIPT})
endforeach()

# ==================================================================
# SET OUTPUT BINARY FILES DIRS
# ==================================================================

if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lib)
include_directories(${CMAKE_BINARY_DIR})
# ===================================================================
# ROOT PATH OF PROJECT
# ===================================================================
set(SRC ${PROJECT_SOURCE_DIR}/src)

# ====================================================================
# APPEND QT LIBRARIES
# ====================================================================
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt${QT_VERSION}::Core Qt${QT_VERSION}::Gui Qt${QT_VERSION}::Widgets)
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

# ====================================================================
# DEFINE SUBDIRECTORIES OF YOUR PROJECT
# ====================================================================

foreach(LIB_PATH IN LISTS INCLUDE_DIRECTORIES)
    add_subdirectory(${LIB_PATH})
endforeach()

# =====================================================================
# DEFINE RESOURCE FILES OF YOUR PROJECT
# =====================================================================

if (QT_VERSION STREQUAL 6)
    qt6_add_resources(RESOURCES ${RESOURCES_FILE_NAME})
else()
    qt5_add_resources(RESOURCES ${RESOURCES_FILE_NAME})
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${RESOURCES} ${APP_ICON_MACOSX})
else()
    add_executable(${PROJECT_NAME} ${RESOURCES})
endif()

# ====================================================================
# INSTALL TARGETS FOR COMPILED RESOURCES
# ====================================================================

#install(TARGETS ${PROJECT_NAME} DESTINATION bin)
#install(TARGETS ${INCLUDE_PROJECT_LIBS} DESTINATION bin/lib)

#install(FILES config DESTINATION bin)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRECTORIES})

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set_source_files_properties(${APP_ICON_MACOSX} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

    set(CURRENT_PROJECT_DIR ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.app/Contents)
    set(BINARY_DIR ${CURRENT_PROJECT_DIR}/MacOS)
    set(RESOURCE_DIR ${CURRENT_PROJECT_DIR}/Resources)
else()
    set(BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/bin)
    set(RESOURCE_DIR ${BINARY_DIR}/resources)
endif()

file(COPY styles DESTINATION ${RESOURCE_DIR})
file(COPY icons DESTINATION ${RESOURCE_DIR})

file(COPY ${INI_FILE} DESTINATION ${RESOURCE_DIR})

# ====================================================================
# DEFILE LIBS OF YOUR PROJECT
# ====================================================================

target_link_libraries(${PROJECT_NAME}
    ${INCLUDE_QT_LIBS}
    ${INCLUDE_PROJECT_LIBS}
)