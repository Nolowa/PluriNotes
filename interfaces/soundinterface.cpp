#include "soundinterface.h"

SoundInterface::SoundInterface(const Sound& s,QWidget *parent) : GeneralInterface(parent), sound(&s){
      layout=new QFormLayout;
      boutonLayout= new QHBoxLayout;
      boutonLayout2= new QHBoxLayout;
      bAddSound= new QPushButton(QString("Ajouter une bande son"));
      generate= new QPushButton(QString("Sauvegarder"));
      bStopMusic= new QPushButton(QString("Stop"));
      bPlayMusic= new QPushButton(QString("Play"));
      titleEdit= new QLineEdit(sound->getTitle(),this);
      descriptionEdit= new QTextEdit(sound->getDescription(),this);
      nameFileSound = new QString(sound->getSoundFileName());
      idEdit= new QLineEdit(sound->getIdentifier().toString(),this);
      idEdit->setReadOnly(1);
      initSound=0;

      //ajustement de la taille des Widgets
      descriptionEdit->setFixedHeight(120);
      titleEdit->setFixedWidth(180);
      idEdit->setFixedWidth(300);

      // ajout des composants sur la layout
      layout->addRow("Identifiant :",idEdit);
      layout->addRow("Titre :",titleEdit);
      layout->addRow("Description :",descriptionEdit);
      boutonLayout->addWidget(generate);
      boutonLayout->addWidget(bAddSound);
      boutonLayout2->addWidget(bStopMusic);
      boutonLayout2->addWidget(bPlayMusic);


      //gestion des Layouts
      mainLayout = new QVBoxLayout;
      mainLayout->addLayout(layout);
      mainLayout->addLayout(boutonLayout);
      mainLayout->addLayout(boutonLayout2);

      setLayout(mainLayout);
      setWindowTitle("Bande Son");

      if(!((*nameFileSound)==QString(""))){
          soundToRegister= new QSound(*nameFileSound);
          initSound=1;
          bAddSound->setEnabled(false);
          soundToRegister->play();
      }

/*
      player = new QMediaPlayer;
      if(!((*nameFileSound)==QString(""))){
        player->setMedia(QUrl::fromLocalFile("/Users/Thibault/Desktop/test.wav"));
        player->setVolume(50);
        player->play();
        bAddSound->setEnabled(false);
      }
*/

      //slot
      QObject::connect(bAddSound, SIGNAL(clicked()), this, SLOT(openSound()));
      QObject::connect(bPlayMusic, SIGNAL(clicked()), this, SLOT(playMusic()));
      QObject::connect(bStopMusic, SIGNAL(clicked()), this, SLOT(stopMusic()));
      QObject::connect(generate, SIGNAL(clicked()), this, SLOT(save()));

      //QObject::connect(bDeleteImage, SIGNAL(clicked()), this, SLOT(deleteImage()));

}


void SoundInterface::setNameFileSound(QString nameSound){
    nameFileSound=&nameSound;
}

//slot
void SoundInterface::openSound(){
      *nameFileSound = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Son (*.wav)");
      QMessageBox::information(this, "Fichier", "Vous avez sélectionné :\n" + *nameFileSound);
      //chargement de l'image sur l'interface graphique
      if(!initSound)
        soundToRegister= new QSound(*nameFileSound);
      bAddSound->setEnabled(false);
      soundToRegister->play();
      initSound=1;
}

void SoundInterface::playMusic(){
    if(initSound)
     soundToRegister->play();

}

void SoundInterface::stopMusic(){
    if(initSound)
     soundToRegister->stop();
}
void SoundInterface::save(){
    Sound * s = new Sound(*sound);
    s->setTitle(titleEdit->text());
    s->setDescription(descriptionEdit->toPlainText());
    s->setSoundFile(*nameFileSound);
    sound = s;
    emit newVersion(s); // signal d'émition pour la création d'une nouvelle version

}
