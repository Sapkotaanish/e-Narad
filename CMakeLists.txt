cmake_minimum_required(VERSION 3.19.8)

project(shareit)

find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})
include_directories(include/)
add_executable(myapp main.cpp src/window.cpp src/welcomePanel.cpp)
target_link_libraries(myapp ${wxWidgets_LIBRARIES})
