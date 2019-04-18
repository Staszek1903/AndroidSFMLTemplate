TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

SOURCES += \
        main.cpp \
    Program.cpp \
    Console.cpp \
    p.cpp \
    touchbuffer.cpp \
    touchable.cpp \
    Renderer.cpp \
    EntityStuff/System.cpp \
    EntityStuff/EntityStuff.cpp \
    ui.cpp

HEADERS += \
    Program.h \
    Console.h \
    p.h \
    touchbuffer.h \
    touchable.h \
    Renderer.h \
    EntityStuff/System.h \
    EntityStuff/EntityStuff.h \
    EntityStuff/Component.h \
    UI.h \
    Singleton.hpp
