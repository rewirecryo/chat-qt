TEMPLATE = app

DESTDIR = bin
TARGET = chat

OBJECTS_DIR = obj

QT = core gui widgets

SOURCES += src/*.cpp src/Requests/*.cpp src/Executors/*.cpp
HEADERS += include/*.hpp include/Requests/*.hpp include/Executors/*.hpp

QMAKE_CXXFLAGS += -g -Wno-unused-parameter -Wno-switch
