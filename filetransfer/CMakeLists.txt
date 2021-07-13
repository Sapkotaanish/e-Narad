project(filetransfer)
set(SFMLinkers -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system)
    add_executable(filetransfer main.cpp src/Client.cpp src/Server.cpp src/Download.cpp)
target_link_libraries(filetransfer ${SFMLinkers})
