#ifndef VERSIONSDOCKVIEW_H
#define VERSIONSDOCKVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListView>
#include <QPushButton>

#include "interfaces/editor/noteframeview.h"
#include "database.h"

class VersionsDockView : public QWidget
{


    Database const * database;
    NoteFrameView const * noteview;

    QPushButton* restoreButton;
    QListView* versionList;
    QVBoxLayout* layout;

    Q_OBJECT
public:
    explicit VersionsDockView(Database const *, NoteFrameView const *, QWidget *parent = 0);

signals:

public slots:
};

#endif // VERSIONSDOCKVIEW_H
