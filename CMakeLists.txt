cmake_minimum_required(VERSION 3.19.8)

project(shareit)

set(CMAKE_CXX_FLAGS "-lsfml-graphics -lsfml-network -lsfml-window -lsfml-system -lpthread")
find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})
include_directories(include/ src/)
add_executable(shareit main.cpp src/window.cpp src/welcomePanel.cpp src/Client.cpp src/Server.cpp src/Timer.cpp)
target_link_libraries(shareit ${wxWidgets_LIBRARIES})
