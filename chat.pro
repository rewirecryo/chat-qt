TEMPLATE = app

DESTDIR = bin
TARGET = chat

OBJECTS_DIR = obj

QT = core gui widgets

SOURCES += src/*.cpp src/Instructions/*.cpp
HEADERS += include/*.hpp include/Instructions/*.hpp

QMAKE_CXXFLAGS += -g
