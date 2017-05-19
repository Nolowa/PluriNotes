#ifndef NOTEFRAMEVIEW_H
#define NOTEFRAMEVIEW_H

#include <QWidget>
#include <QHBoxLayout>
#include "notes/note.h"


class NoteFrameView : public QWidget
{
    Q_OBJECT

    QWidget* widget;
    QHBoxLayout* layout;

    void initUI();
    void buildNoteUI(Note& note);

public:
    explicit NoteFrameView(QWidget *parent = 0);


signals:

public slots:
    void setNote(const Note * note);
};

#endif // NOTEFRAMEVIEW_H
