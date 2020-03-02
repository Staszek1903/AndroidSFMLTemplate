TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

#LIBS +=-L/usr/lib/ -lboost_system -lboost_chrono -lboost_thread -lboost_timer

DEFINES += DEBUG_BUILD

SOURCES += \
    EntityStuff/componentcontainer.cpp \
    EntityStuff/event.cpp \
    EntityStuff/eventmanager.cpp \
    EntityStuff/sizemap.cpp \
    IOStuff/console.cpp \
    IOStuff/line.cpp \
    IOStuff/program.cpp \
    IOStuff/programstage.cpp \
    IOStuff/renderer.cpp \
    IOStuff/touchable.cpp \
    IOStuff/touchbuffer.cpp \
    IOStuff/ui.cpp \
    IOStuff/vect.cpp \
    PlatformerStuff/colidable.cpp \
    PlatformerStuff/colisiondata.cpp \
    PlatformerStuff/dynamic.cpp \
    PlatformerStuff/guidable.cpp \
    PlatformerStuff/steeringmanager.cpp \
    PlatformerStuff/tilemap.cpp \
    ScriptStuff/parser.cpp \
    ScriptStuff/script.cpp \
    ScriptStuff/scriptentry.cpp \
    main.cpp \
    p.cpp \
    EntityStuff/system.cpp \
    EntityStuff/entity.cpp \
    EntityStuff/entitymanager.cpp \
    EntityStuff/componentmanager.cpp \
    EntityStuff/entity_stuff.cpp \
    EntityStuff/systemmanager.cpp \
    EntityStuff/component.cpp

HEADERS += \
    EntityStuff/event.h \
    EntityStuff/eventmanager.h \
    EntityStuff/pool.hpp \
    EntityStuff/sizemap.h \
    IOStuff/console.h \
    IOStuff/line.h \
    IOStuff/program.h \
    IOStuff/programstage.h \
    IOStuff/renderer.h \
    IOStuff/resource_getter.h \
    IOStuff/resource_manager.h \
    IOStuff/singleton.hpp \
    IOStuff/touchable.h \
    IOStuff/touchbuffer.h \
    IOStuff/ui.h \
    IOStuff/vect.h \
    PlatformerStuff/colidable.h \
    PlatformerStuff/colisiondata.h \
    PlatformerStuff/dynamic.h \
    PlatformerStuff/guidable.h \
    PlatformerStuff/steeringmanager.h \
    PlatformerStuff/tilemap.h \
    ScriptStuff/colidable.h \
    ScriptStuff/parser.h \
    ScriptStuff/script.h \
    ScriptStuff/scriptentry.h \
    p.h \
    EntityStuff/system.h \
    EntityStuff/entity_stuff.h \
    EntityStuff/entity.h \
    EntityStuff/entitymanager.h \
    EntityStuff/component.h \
    EntityStuff/systemmanager.h \
    EntityStuff/componentmanager.h \
    EntityStuff/componentcontainer.h

DISTFILES += \
    Arial.ttf \
    levels/dev_room.lvl \
    sfmltemp.supp \
    textures/textures.conf
