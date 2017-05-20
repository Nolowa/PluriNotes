#ifndef NOTEFRAMEVIEW_H
#define NOTEFRAMEVIEW_H

#include <QWidget>
#include <QHBoxLayout>
#include "notes/note.h"
#include "noteinterface.h"

class NoteFrameView : public QWidget
{
    Q_OBJECT

    NoteInterface* widget;
    QHBoxLayout* layout;

    void initUI();
    void buildNoteUI(Note& note);

public:
    explicit NoteFrameView(QWidget *parent = 0);


signals:
    void noteUpdated(const Note * note);
public slots:
    void setNote(const Note * note);
};

#endif // NOTEFRAMEVIEW_H
