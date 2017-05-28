QT += core
QT += gui
QT += multimediawidgets
QT += sql
CONFIG += c++11

TARGET = Projet
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    notes/note.cpp \
    notesmanager.cpp \
    notes/article.cpp \
    notes/task.cpp \
    notes/image.cpp \
    notes/video.cpp \
    notes/sound.cpp \
    notes/notextualnote.cpp \
    memento.cpp \
    version.cpp \
    interfaces/articleinterface.cpp \
    interfaces/taskinterface.cpp \
    interfaces/imageinterface.cpp \
    interfaces/soundinterface.cpp \
    interfaces/videointerface.cpp \
    corbeille.cpp \
    interfaces/mainframe.cpp \
    interfaces/noteslistview.cpp \
    interfaces/noteframeview.cpp \
    interfaces/noteinterface.cpp \
    interfaces/mainwindow.cpp \
    interfaces/corbeillelistview.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS +=\
    notes/note.h \
    notesmanager.h \
    utils.h \
    notes/article.h \
    notes/task.h \
    notes/image.h \
    notes/video.h \
    notes/sound.h \
    notes/notextualnote.h \
    memento.h \
    version.h \
    interfaces/articleinterface.h \
    interfaces/taskinterface.h \
    interfaces/imageinterface.h \
    interfaces/soundinterface.h \
    interfaces/videointerface.h \
    relations/relationship.h \
    relations/relationsmanager.h \
    relations/association.h \
    relations/bidirectionalrelationship.h \
    corbeille.h \
    interfaces/mainframe.h \
    interfaces/noteslistview.h \
    interfaces/noteframeview.h \
    interfaces/noteinterface.h \
    interfaces/mainwindow.h \
    interfaces/corbeillelistview.h

RESOURCES += \
    resources.qrc

