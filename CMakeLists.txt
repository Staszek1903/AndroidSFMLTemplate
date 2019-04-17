cmake_minimum_required(VERSION 3.7.2)

find_package(SFML 2 REQUIRED COMPONENTS graphics audio)

# all source files
set(SRC main.cpp P.cpp Program.cpp Console.cpp touchbuffer.cpp Renderer.cpp touchable.cpp UI.cpp)

# define the pong target
add_executable(exec ${SRC})
target_link_libraries(exec sfml-audio sfml-graphics)