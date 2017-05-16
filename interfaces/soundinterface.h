#ifndef SOUNDINTERFACE_H
#define SOUNDINTERFACE_H


#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QObject>
#include <QMessageBox>
#include <QFileDialog>
#include <QMediaPlayer>

#include "notes/sound.h"
class Sound;



class SoundInterface : public QWidget{
    Q_OBJECT

    Sound* sound;
    QSound* soundToRegister;
    QString* nameFileSound;
    QLabel* labelSound;
    QLineEdit* titleEdit;
    QLineEdit* idEdit;
    QTextEdit* descriptionEdit;
    QFormLayout* layout;
    QVBoxLayout *mainLayout;
    QHBoxLayout* boutonLayout;
    QHBoxLayout* boutonLayout2;
    QPushButton* generate;
    QPushButton* bAddSound;
    QPushButton* bStopMusic;
    QPushButton* bPlayMusic;
    bool initSound;
    //QMediaPlayer* player;


public :
    SoundInterface(Sound* s,QWidget *parent = 0);
    void setNameFileSound(QString nameSound);

public slots :
    void openSound();
    void playMusic();
    void stopMusic();
    void save();
};

#endif // SOUNDINTERFACE_H
