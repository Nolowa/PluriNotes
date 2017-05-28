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

    QFormLayout* boxLayout;
    QComboBox * versions;
    QPushButton* choisir;
    int Id;
    std::vector <int> a;

    //QPushButton* bDeleteImage;
    //bool deletedImage;

public:
    ImageInterface(const Image& im, QWidget *parent = 0);
    void setNameFileImage(QString nameImage);
    void parcourir();

public slots :
    void openImage();
    void fitToWindow();
    void save();
    //void deleteImage();
    void charger();
    void enregistrerid(int i);
};

#endif // IMAGEINTERFACE_H
