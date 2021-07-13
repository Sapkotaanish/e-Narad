cmake_minimum_required(VERSION 3.19.8)

project(shareit)
<<<<<<< HEAD
find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})
include_directories(include/ src/)
add_executable(myapp main.cpp src/window.cpp src/welcomePanel.cpp src/Client.cpp src/Server.cpp src/Timer.cpp)
target_link_libraries(myapp ${wxWidgets_LIBRARIES} sfml-network sfml-system)
=======
set(CMAKE_CXX_FLAGS "-lsfml-graphics -lsfml-network -lsfml-window -lsfml-system -lpthread")
find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})
include_directories(include/ src/)
add_executable(shareit main.cpp src/window.cpp src/welcomePanel.cpp src/Client.cpp src/Server.cpp src/Timer.cpp)
target_link_libraries(shareit ${wxWidgets_LIBRARIES})
>>>>>>> 9b5ac9b0ba51a33dcacfbbe2495082f2f8007314
