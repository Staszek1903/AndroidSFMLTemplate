TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

SOURCES += \
        main.cpp \
    p.cpp \
    touchbuffer.cpp \
    touchable.cpp \
    ui.cpp \
    EntityStuff/component.cpp \
    EntityStuff/system.cpp \
    EntityStuff/entity_stuff.cpp \
    console.cpp \
    renderer.cpp \
    program.cpp \
    EntityStuff/entity.cpp \
    EntityStuff/componentcontainer.cpp

HEADERS += \
    p.h \
    touchbuffer.h \
    touchable.h \
    EntityStuff/component.h \
    EntityStuff/entity_stuff.h \
    EntityStuff/system.h \
    console.h \
    program.h \
    renderer.h \
    singleton.hpp \
    ui.h \
    EntityStuff/entity.h \
    EntityStuff/componentcontainer.h
