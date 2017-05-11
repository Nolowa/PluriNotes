QT += core
QT += gui
QT += multimediawidgets

CONFIG += c++11

TARGET = Projet
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    note.cpp \
    notesmanager.cpp \
    article.cpp \
    task.cpp \
    image.cpp \
    video.cpp \
    sound.cpp \
    notextualnote.cpp \
    plurinotes.cpp \
    memento.cpp \
    version.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    note.h \
    notesmanager.h \
    utils.h \
    article.h \
    task.h \
    image.h \
    video.h \
    sound.h \
    notextualnote.h \
    plurinotes.h \
    memento.h \
    version.h
