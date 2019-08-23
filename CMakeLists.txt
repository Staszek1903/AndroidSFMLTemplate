cmake_minimum_required(VERSION 3.7.2)

find_package(SFML 2 REQUIRED COMPONENTS graphics audio)

# all source files
set(SRC main.cpp p.cpp IOStuff/program.cpp IOStuff/console.cpp  IOStuff/touchbuffer.cpp   IOStuff/renderer.cpp IOStuff/touchable.cpp  IOStuff/ui.cpp  EntityStuff/entity_stuff.cpp EntityStuff/system.cpp EntityStuff/component.cpp EntityStuff/entity.cpp EntityStuff/componentcontainer.cpp  EntityStuff/componentmanager.cpp EntityStuff/entitymanager.cpp EntityStuff/systemmanager.cpp EntityStuff/event.cpp EntityStuff/eventmanager.cpp ScriptStuff/script.cpp ScriptStuff/scriptentry.cpp ScriptStuff/parser.cpp IOStuff/programstage.cpp IOStuff/line.cpp PlatformerStuff/colidable.cpp  PlatformerStuff/dynamic.cpp   PlatformerStuff/tilemap.cpp   IOStuff/vect.cpp )
 
# define the pong target
add_executable(exec ${SRC})

target_link_libraries(exec sfml-audio sfml-graphics)