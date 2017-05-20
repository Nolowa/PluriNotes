#include "videointerface.h"

VideoInterface::VideoInterface(const Video& vid,QWidget *parent) : NoteInterface(parent), video(&vid){
    QSize iconSize(36, 36);
    //layout
    layout=new QFormLayout;
    boutonLayout= new QHBoxLayout;
    boutonLayout2= new QHBoxLayout;
    //bouton sauvegarder
    generate= new QPushButton(QString("Sauvegarder"));

    //BoutonStopVideo
    stopButton = new QToolButton;
    stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    stopButton->setIconSize(iconSize);
    stopButton->setToolTip(tr("Stop"));
    //bStopVideo= new QPushButton(QString("Stop"));

    //boutonPlay
    playButton = new QToolButton;
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    playButton->setIconSize(iconSize);
    playButton->setToolTip(tr("Play"));
    //playButton= new QPushButton(QString("Play"));

    //boutonOpenFile
    openButton= new QToolButton;
    openButton->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    openButton->setIconSize(iconSize);
    openButton->setToolTip(tr("Open File"));
    //openButton= new QPushButton(QString("Ajouter une Video"));


    //boutonPause
    pauseButton = new QToolButton;
    pauseButton->setCheckable(true);
    pauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    pauseButton->setIconSize(iconSize);
    pauseButton->setToolTip(tr("Pause"));

    titleEdit= new QLineEdit(video->getTitle(),this);
    descriptionEdit= new QTextEdit(video->getDescription(),this);
    nameFileVideo= new QString(video->getVideoFileName());
    idEdit= new QLineEdit(video->getIdentifier().toString(),this);
    idEdit->setReadOnly(1);
    initVideo=0;

    //partie video
    graphicsView = new QGraphicsView;
    player = new QMediaPlayer;
    layoutVideo = new QHBoxLayout;

    scene = new QGraphicsScene;
    item = new QGraphicsVideoItem;
    //graphicsView->showFullScreen();
    //graphicsView->scale(graphicsView->width(), graphicsView->height());

    //ajustement de la taille des Widgets
    descriptionEdit->setFixedHeight(120);
    titleEdit->setFixedWidth(180);
    idEdit->setFixedWidth(300);


    // ajout des composants sur la layout
    layout->addRow("Identifiant :",idEdit);
    layout->addRow("Titre :",titleEdit);
    layout->addRow("Description :",descriptionEdit);
    layoutVideo->addWidget(graphicsView);
    boutonLayout->addStretch();
    boutonLayout->addWidget(openButton);
    boutonLayout->addWidget(playButton);
    boutonLayout->addWidget(pauseButton);
    boutonLayout->addWidget(stopButton);
    boutonLayout->addStretch();
    boutonLayout2->addWidget(generate);


    //gestion des Layouts
    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layout);
    mainLayout->addLayout(layoutVideo);
    mainLayout->addLayout(boutonLayout);
    mainLayout->addLayout(boutonLayout2);

    setLayout(mainLayout);
    setWindowTitle("Video");


    if(!((*nameFileVideo)==QString(""))){
        videoToRegister= new QMovie(*nameFileVideo);
        graphicsView->setScene(scene);
        graphicsView->setFixedSize(350,185);
        player->setVideoOutput(item);
        graphicsView->scene()->addItem(item);
        player->setMedia(QUrl::fromLocalFile(*nameFileVideo));
        player->play();
        initVideo=1;
        openButton->setEnabled(false);
    }

    //slot
    QObject::connect(openButton, SIGNAL(clicked()), this, SLOT(openVideo()));
    QObject::connect(playButton, SIGNAL(clicked()), this, SLOT(playVideo()));
    QObject::connect(stopButton, SIGNAL(clicked()), this, SLOT(stopVideo()));
    QObject::connect(pauseButton, SIGNAL(clicked()), this, SLOT(pauseVideo()));
    QObject::connect(generate, SIGNAL(clicked()), this, SLOT(save()));


}


//slot
void VideoInterface::openVideo(){
      *nameFileVideo = QFileDialog::getOpenFileName(this, "Ouvrir une vidéo", QString(), "Video (*.mp4 *.avi)");
      QMessageBox::information(this, "Fichier", "Vous avez sélectionné :\n" + *nameFileVideo);
      //chargement de l'image sur l'interface graphique
      if(!initVideo)
        videoToRegister= new QMovie(*nameFileVideo);
      openButton->setEnabled(false);
      graphicsView->setScene(scene);
      graphicsView->setFixedSize(350,185);
      player->setVideoOutput(item);
      graphicsView->scene()->addItem(item);
      player->setMedia(QUrl::fromLocalFile(*nameFileVideo));
      player->play();
      initVideo=1;
}

void VideoInterface::pauseVideo(){
    if (pauseButton->isChecked())
        player->pause();
    else
        player->play();

}

void VideoInterface::playVideo(){
    player->play();
    pauseButton->setChecked(0);
}

void VideoInterface::stopVideo(){
    player->stop();
}

void VideoInterface::save(){
    Video * v = new Video(*video);
    v->setTitle(titleEdit->text());
    v->setDescription(descriptionEdit->toPlainText());
    v->setVideoFile(*nameFileVideo);

    video = v;
    emit newVersion(v); // signal d'émition pour la création d'une nouvelle version
}

void VideoInterface::updateButtons(){
    /*playButton->setEnabled(movie->isValid() && movie->frameCount() != 1
                           && movie->state() == QMovie::NotRunning);
    pauseButton->setEnabled(movie->state() != QMovie::NotRunning);
    pauseButton->setChecked(movie->state() == QMovie::Paused);
    stopButton->setEnabled(movie->state() != QMovie::NotRunning);
    */
}
