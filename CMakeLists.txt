cmake_minimum_required(VERSION 3.19.8)

project(e-Narad)

set(CMAKE_CXX_FLAGS "-lsfml-graphics -lsfml-network -lsfml-window -lsfml-system -lpthread -lX11")
find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})
include_directories(include/ src/)
add_executable(sf-eNarad main.cpp src/window.cpp src/welcomePanel.cpp src/Client.cpp src/Server.cpp src/Timer.cpp src/Board.cpp)
target_link_libraries(sf-eNarad ${wxWidgets_LIBRARIES})
