TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

SOURCES += \
        main.cpp \
    console.cpp \
    p.cpp \
    program.cpp \
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
    EntityStuff/componentcontainer.cpp

HEADERS += \
    console.h \
    p.h \
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
    EntityStuff/componentcontainer.h
