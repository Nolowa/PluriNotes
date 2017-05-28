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
#include <QComboBox>
#include <QVector>

#include "noteinterface.h"
#include "notes/sound.h"
class Sound;



class SoundInterface : public NoteInterface{
    Q_OBJECT

    const Sound* sound;
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
    /**< la partie choisir et charger les versions */
    QFormLayout* boxLayout;
    QComboBox * versions;
    QPushButton* choisir;
    int Id;
    std::vector <int> a;

    QPushButton* activer;/**< archive->active */
    QPushButton* supprimer;/**< supprimer */

public :
    SoundInterface(const Sound& s, QWidget *parent = 0);
    SoundInterface(const Sound& s, int i, QWidget *parent = 0);/**< l'interface pour les notes non éditable */
    void setNameFileSound(QString nameSound);
    void parcourir();/**< parcourir les versions*/

public slots :
    void openSound();
    void playMusic();
    void stopMusic();
    void save();
    void charger();/**< charger la version*/
    void enregistrerid(int i);/**< garder id présent*/
};

#endif // SOUNDINTERFACE_H
