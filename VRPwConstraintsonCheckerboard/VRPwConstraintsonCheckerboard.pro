TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        client.cpp \
        damier.cpp \
        lecturetxt.cpp \
        main.cpp \
        obstacle.cpp \
        plateau.cpp \
        probleme.cpp \
        robot.cpp

HEADERS += \
    client.h \
    damier.h \
    lecturetxt.h \
    obstacle.h \
    plateau.h \
    probleme.h \
    robot.h
