#include "imageinterface.h"

ImageInterface::ImageInterface(const Image& im, QWidget *parent): NoteInterface(parent), image(&im){
    layout=new QFormLayout;
    boutonLayout = new QHBoxLayout;
    bAddImage= new QPushButton(QString("Ajouter une image"));
    generate= new QPushButton(QString("Sauvegarder"));
    //bDeleteImage= new QPushButton(QString("Supprimer l'image"));
    //deletedImage=0;
    nameFileImage= new QString(image->getnameFile());
    idEdit= new QLineEdit(image->getIdentifier().toString(),this);
    idEdit->setReadOnly(1);

    titleEdit= new QLineEdit(image->getTitle(),this);
    descriptionEdit= new QTextEdit(image->getDescription(),this);

    // Espace pour l'image
    imageLabel = new QLabel("Pas d'image chargé");
    imageLabel->setAlignment(Qt::AlignCenter);
    //imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setBackgroundRole(QPalette::Dark);
    imageLabel->setAutoFillBackground(true);
    fitCheckBox = new QCheckBox("Fit to Window");
    QHBoxLayout* layoutImage = new QHBoxLayout;
    layoutImage->addStretch();
    layoutImage->addWidget(imageLabel);
    layoutImage->addStretch();
    imageLabel->setFixedSize(264,144);


    //ajustement de la taille des Widgets
    descriptionEdit->setFixedHeight(120);
    titleEdit->setFixedWidth(180);
    idEdit->setFixedWidth(300);

    // ajout des composants sur la layout
    layout->addRow("Identifiant :",idEdit);
    layout->addRow("Titre :",titleEdit);
    layout->addRow("Description :",descriptionEdit);
    boutonLayout->addWidget(generate);
    boutonLayout->addWidget(bAddImage);
    //boutonLayout->addWidget(bDeleteImage);

    //gestion des Layouts
    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layout);
    //mainLayout->addWidget(imageLabel);
    mainLayout->addLayout(layoutImage);
    mainLayout->addWidget(fitCheckBox);
    mainLayout->addLayout(boutonLayout);

    setLayout(mainLayout);
    setWindowTitle("Image");
    resize(400, 400);


    //Si déjà présence d'une image l'afficher directement!
    if(!(image->getImage().isNull())){
        //imageLabel->setPixmap(QPixmap::fromImage(image->getImage()).scaled(QSize(213,10)));
        imageLabel->setPixmap(QPixmap(*nameFileImage));
        //layout->addWidget(imageLabel);
        imageLabel->show();
        bAddImage->setEnabled(false);
    }

    //slot
    QObject::connect(bAddImage, SIGNAL(clicked()), this, SLOT(openImage()));
    QObject::connect(fitCheckBox, SIGNAL(clicked()), this, SLOT(fitToWindow()));
    QObject::connect(generate, SIGNAL(clicked()), this, SLOT(save()));

    //QObject::connect(bDeleteImage, SIGNAL(clicked()), this, SLOT(deleteImage()));

}


void ImageInterface::setNameFileImage(QString nameImage){
    nameFileImage=&nameImage;
}

//slot
void ImageInterface::openImage(){
    nameFileImage = new QString();
    *nameFileImage = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg *.bmp)");
    QMessageBox::information(this, "Fichier", "Vous avez sélectionné :\n" + *nameFileImage);
    //chargement de l'image sur l'interface graphique
    imageToRegister= new QImage(*nameFileImage);
    imageLabel->setPixmap(QPixmap(*nameFileImage));
    imageLabel->show();
    bAddImage->setEnabled(false);

}

void ImageInterface::fitToWindow(){
     imageLabel->setScaledContents(fitCheckBox->isChecked());
}

void ImageInterface::save(){
    Image* i = new Image(*image);
    i->setDescription(descriptionEdit->toPlainText());
    i->setTitle(titleEdit->text());
    i->setImage(*nameFileImage);

    image = i;
    emit newVersion(i); // signal d'émition pour la création d'une nouvelle version
    //QMessageBox::information(this, "Fichier", "Enregistrement :\n" +titleEdit->text()+"\n"+descriptionEdit->toPlainText() +"\n"+ *nameFileImage);
}

/* // si on souhaite pouvoir changer une image de la note (fonction que ne n'utilisons pas car c'est contraire au principe d'une note)
void ImageInterface::deleteImage(){
    delete imageLabel;
    //nameFileImage=0;
    setNameFileImage(nullptr);
    QMessageBox::information(this, "Fichier", "Vous avez supprimé :\n" + *nameFileImage);
    deletedImage=1;
    bAddImage->setEnabled(true);
}
*/
