#ifndef NOTEFRAMEVIEW_H
#define NOTEFRAMEVIEW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include "notes/noteholder.h"
#include "interfaces/content-editor/noteinterface.h"

class NoteFrameView : public QWidget
{
    Q_OBJECT

    const NoteHolder* note;

    NoteInterface* widget;
    QVBoxLayout* layout;

    QWidget* btns_bar;
    QHBoxLayout* btns_bar_l;

    QPushButton* save_btn;
    QPushButton* copy_id_btn;
    QPushButton* delete_btn;

    void initUI();

public:
    explicit NoteFrameView(QWidget *parent = 0);


signals:
    void noteSaved(const NoteHolder&, const Note& body);
public slots:
    void setNote(const NoteHolder * note);
    void save();
};

#endif // NOTEFRAMEVIEW_H
