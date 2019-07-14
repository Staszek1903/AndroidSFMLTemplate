TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

#LIBS +=-L/usr/lib/ -lboost_system -lboost_chrono -lboost_thread -lboost_timer


debug {
  DEFINES += DEBUG_BUILD
}

SOURCES += \
    EntityStuff/event.cpp \
    EntityStuff/eventmanager.cpp \
    EntityStuff/sizemap.cpp \
    PlatformerStuff/colidable.cpp \
    PlatformerStuff/dynamic.cpp \
    PlatformerStuff/steeringmanager.cpp \
    PlatformerStuff/tilemap.cpp \
    ScriptStuff/parser.cpp \
    ScriptStuff/script.cpp \
    ScriptStuff/scriptentry.cpp \
    error_generate.cpp \
    line.cpp \
        main.cpp \
    console.cpp \
    p.cpp \
    program.cpp \
    programstage.cpp \
    ui.cpp \
    touchable.cpp \
    touchbuffer.cpp \
    renderer.cpp \
    EntityStuff/system.cpp \
    EntityStuff/entity.cpp \
    EntityStuff/entitymanager.cpp \
    EntityStuff/componentmanager.cpp \
    EntityStuff/entity_stuff.cpp \
    EntityStuff/systemmanager.cpp \
    EntityStuff/component.cpp \
    EntityStuff/componentcontainer.cpp \
    vect.cpp

HEADERS += \
    EntityStuff/event.h \
    EntityStuff/eventmanager.h \
    EntityStuff/sizemap.h \
    PlatformerStuff/colidable.h \
    PlatformerStuff/dynamic.h \
    PlatformerStuff/steeringmanager.h \
    PlatformerStuff/tilemap.h \
    ScriptStuff/colidable.h \
    ScriptStuff/parser.h \
    ScriptStuff/script.h \
    ScriptStuff/scriptentry.h \
    console.h \
    error_generate.hpp \
    line.h \
    p.h \
    programstage.h \
    resource_getter.h \
    resource_manager.h \
    touchable.h \
    renderer.h \
    program.h \
    touchbuffer.h \
    ui.h \
    singleton.hpp \
    EntityStuff/system.h \
    EntityStuff/entity_stuff.h \
    EntityStuff/entity.h \
    EntityStuff/entitymanager.h \
    EntityStuff/component.h \
    EntityStuff/systemmanager.h \
    EntityStuff/componentmanager.h \
    EntityStuff/componentcontainer.h \
    vect.h

DISTFILES += \
    Arial.ttf \
    levels/dev_room.lvl \
    sfmltemp.supp \
    textures/textures.conf
