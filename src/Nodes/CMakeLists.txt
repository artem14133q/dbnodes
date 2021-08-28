set(LIBRARY_NAME Nodes)

set(RESOURCES
        TableNode.cpp
        TableNode.h
        Table/Column.cpp
        Table/Column.h)

add_library(${LIBRARY_NAME} STATIC ${RESOURCES})

set(REQUIRED_LIBS_QUALIFIED Qt${QT_VERSION}::Core Qt${QT_VERSION}::Widgets)

# INCLUDE PROJECT SUBDIRECTORIES
set(PROJECT_DIRECTORIES
        ${SRC}/Abstract
        ${SRC}/Dictionaries)

# INCLUDE PROJECT LIBS
set(PROJECT_LIBS
        Abstract
        Dictionaries)

include_directories(${CMAKE_BINARY_DIR})
target_include_directories(${LIBRARY_NAME} PUBLIC ${PROJECT_DIRECTORIES})
target_link_libraries(${LIBRARY_NAME} ${REQUIRED_LIBS_QUALIFIED} ${PROJECT_LIBS})