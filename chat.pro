TEMPLATE = app

DESTDIR = bin
TARGET = chat

OBJECTS_DIR = obj

QT = core gui widgets

SOURCES += src/*.cpp
HEADERS += include/*.hpp

QMAKE_CXXFLAGS += -g
