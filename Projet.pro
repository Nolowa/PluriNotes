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
<<<<<<< HEAD
    notextualnote.cpp \
    plurinotes.cpp
=======
<<<<<<< HEAD
    memento.cpp \
    version.cpp
=======
    notextualnote.cpp
>>>>>>> 2f9f21b47e70ca72c232bc96d8d099876066e253
>>>>>>> 7744f4ea025981c698d5ebac340ee5e6c9d78ec4

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
<<<<<<< HEAD
    notextualnote.h \
    plurinotes.h
=======
<<<<<<< HEAD
    memento.h \
    version.h
=======
    notextualnote.h
>>>>>>> 2f9f21b47e70ca72c232bc96d8d099876066e253
>>>>>>> 7744f4ea025981c698d5ebac340ee5e6c9d78ec4