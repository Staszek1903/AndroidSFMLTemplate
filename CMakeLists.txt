cmake_minimum_required(VERSION 3.7.2)

find_package(SFML 2 REQUIRED COMPONENTS graphics audio)

# all source files
set(SRC main.cpp p.cpp program.cpp console.cpp touchbuffer.cpp renderer.cpp touchable.cpp ui.cpp EntityStuff/entity_stuff.cpp EntityStuff/system.cpp
EntityStuff/component.cpp)

# define the pong target
add_executable(exec ${SRC})
target_link_libraries(exec sfml-audio sfml-graphics)