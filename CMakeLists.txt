cmake_minimum_required(VERSION 3.10)

# Add folder where are supportive functions
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Include Qt basic functions
include(QtCommon)

# Basic information about project

project(tictactoelr VERSION 1.0)

# Set PROJECT_VERSION_PATCH and PROJECT_VERSION_TWEAK to 0 if not present, needed by add_project_meta
fix_project_version()


# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE_FILES
        src/glwidget.cpp
        src/mainwindow.cpp
        src/window.cpp
        src/Drawable.cpp
        src/PlayerX.cpp
        src/PlayerO.cpp
        src/main.cpp
        src/LogicHandler.cpp 
        )

add_project_meta(META_FILES_TO_INCLUDE)

find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGL OpenGLWidgets)

add_executable(${PROJECT_NAME} ${OS_BUNDLE} # Expands to WIN32 or MACOS_BUNDLE depending on OS
    ${SOURCE_FILES} ${META_FILES_TO_INCLUDE} ${RESOURCE_FILES}
)

target_link_libraries(${PROJECT_NAME} Qt6::Widgets Qt6::OpenGL Qt6::OpenGLWidgets)

# Copy resources to build directory
add_custom_target(copy_res ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res ${CMAKE_BINARY_DIR}/res
)

add_dependencies(${PROJECT_NAME} copy_res)
