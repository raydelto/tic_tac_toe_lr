# Reference: http://qt-project.org/doc/qt-5.0/qtdoc/cmake-manual.html

cmake_minimum_required(VERSION 3.0)

# Add folder where are supportive functions
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Include Qt basic functions
include(QtCommon)

# Basic information about project

project(tictactoelr VERSION 1.0)

# Set PROJECT_VERSION_PATCH and PROJECT_VERSION_TWEAK to 0 if not present, needed by add_project_meta
fix_project_version()


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

find_package(Qt6Widgets REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS OpenGL OpenGLWidgets)


add_executable(${PROJECT_NAME} ${OS_BUNDLE} # Expands to WIN32 or MACOS_BUNDLE depending on OS
    ${SOURCE_FILES} ${META_FILES_TO_INCLUDE} ${RESOURCE_FILES}
)

target_link_libraries(${PROJECT_NAME} Qt6::Widgets Qt6::OpenGL Qt6::OpenGLWidgets)
