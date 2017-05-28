#ifndef IMAGEINTERFACE_H
#define IMAGEINTERFACE_H

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
#include <QCheckBox>
#include <QStyle>
#include <QComboBox>
#include <QVector>

#include "noteinterface.h"
#include "notes/image.h" // inclusion récursif.?

class Image;

class ImageInterface: public NoteInterface {
    Q_OBJECT

    const Image* image;
    QImage* imageToRegister;
    QString* nameFileImage;
    QLabel* imageLabel;
    QLineEdit* titleEdit;
    QLineEdit* idEdit;
    QTextEdit* descriptionEdit;
    QFormLayout* layout;
    QVBoxLayout *mainLayout;
    QHBoxLayout* boutonLayout;
    QPushButton* generate;
    QPushButton* bAddImage;
    QCheckBox* fitCheckBox;
    /**< la partie choisir et charger les versions */
    QFormLayout* boxLayout;
    QComboBox * versions;
    QPushButton* choisir;
    int Id;
    std::vector <int> a;

    QPushButton* activer;/**< archive->active */
    QPushButton* supprimer;/**< supprimer */
    //QPushButton* bDeleteImage;
    //bool deletedImage;

public:
    ImageInterface(const Image& im, QWidget *parent = 0);
    ImageInterface(const Image& im, int i, QWidget *parent = 0);/**< l'interface pour les notes non éditable */
    void setNameFileImage(QString nameImage);
    void parcourir();/**< parcourir les versions*/

public slots :
    void openImage();
    void fitToWindow();
    void save();
    //void deleteImage();
    void charger();/**< charger la version*/
    void enregistrerid(int i);/**< garder id présent*/
};

#endif // IMAGEINTERFACE_H
