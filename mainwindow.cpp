#include <mainwindow.h>
#include<QApplication>
#include<QWidget>
#include<QSlider>
#include<QPushButton>
#include<QVBoxLayout>
#include<QMessageBox>
#include<QLCDNumber>
#include<QLabel>
#include<QGridLayout>
#include<QDoubleValidator>
#include<QVector>
#include"calculsAlignement.h"
#include <vector>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "sdlglutils.h"
#include <display_opengl.h>
#include<QGLWidget>
#include <GL/gl.h>
#include <GL/glu.h>
#include<QGLWidget>
#include"display_opengl.h"
#include "sdlglutils.h"
#include "planetselection.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)

{


        this->resize(640,480);
    enterProgram = new QPushButton(tr("entrer"));
    connect(enterProgram,SIGNAL(clicked(bool)),this,SLOT(window1()));
    Layout1 = new QVBoxLayout;
    Layout1->addWidget(enterProgram);
    setLayout(Layout1);
    numeroplanete=0;

}

void MainWindow::window1(){
    nbplanetes = new QSlider(Qt::Horizontal);
    nbplanetes->setValue(0);
    nbplanetes->setRange(0,15);
    nbplanetesLabel = new QLabel(tr("nombre de planètes:"));

    valider = new QPushButton(tr("&valider"));

    masseEtoile = new QSlider(Qt::Horizontal);
    masseEtoile->setValue(0);
    masseEtoile->setRange(0,99999);
    masseEtoileLabel = new QLabel(tr("masse de l'étoile"));

    lcdMasseEtoile = new QLCDNumber(5);
    lcdNbplanetes = new QLCDNumber(2);
    selectionnerFond = new QPushButton(tr("selectionner fond"));
    toto= new MyGLWidget;
    enterProgram->hide();

    Layout1->addWidget(masseEtoileLabel);
    Layout1->addWidget(lcdMasseEtoile);
    Layout1->addWidget(masseEtoile);
    Layout1->addWidget(nbplanetesLabel);
    Layout1->addWidget(lcdNbplanetes);
    Layout1->addWidget(nbplanetes);
    Layout1->addWidget(toto);
    Layout1->addWidget(selectionnerFond);
    Layout1->addWidget(valider);
    setLayout(Layout1);


    connect(masseEtoile,SIGNAL(valueChanged(int)),lcdMasseEtoile,SLOT(display(int)));
    connect(nbplanetes,SIGNAL(valueChanged(int)),lcdNbplanetes,SLOT(display(int)));
    connect(valider,SIGNAL(clicked()),this,SLOT(solarSelection()));
    connect(selectionnerFond,SIGNAL(clicked()),this, SLOT(indiceFond()));
    connect(selectionnerFond,SIGNAL(clicked()),toto, SLOT(refresh()));

}


void MainWindow::solarSelection()
{
    if(nbplanetes->value() == 0 || masseEtoile->value() == 0){
    QMessageBox msg;
    msg.setText(tr("entrez au moins une planète ainsi que la masse de l'étoile"));
    msg.exec();
    }else{
    delete masseEtoileLabel;
    delete lcdMasseEtoile;
    delete nbplanetesLabel;
    delete lcdNbplanetes;
    delete valider;
    delete selectionnerFond;
    delete toto;
    SDL_Quit();
    delete Layout1;
    nbplanetes->hide();
    masseEtoile->hide();

    valider2 = new QPushButton(tr("valider"));
    precedent = new QPushButton(tr("précédent"));
    suivant = new QPushButton(tr("suivant"));
    solarSize = new QSlider(Qt::Horizontal);
    solarSize->setValue(1);
    solarSize->setRange(1,8);
    toto2 = new SolarSelectionGLWidget;
    tailleSoleil = new QLabel(tr("taille de l'étoile"));

    Layout2 = new QGridLayout;
    Layout2->addWidget(suivant,2,2);
    Layout2->addWidget(precedent,2,1);
    Layout2->addWidget(toto2,0,1,1,2);
    Layout2->addWidget(solarSize,1,2);
    Layout2->addWidget(tailleSoleil,1,1);
    Layout2->addWidget(valider2,3,2);

    setLayout(Layout2);
    connect(valider2,SIGNAL(clicked()),this,SLOT(window2()));
    connect(precedent,SIGNAL(clicked()),toto2,SLOT(goDown()));
    connect(suivant,SIGNAL(clicked()),toto2,SLOT(goUp()));
    connect(precedent,SIGNAL(clicked()),this,SLOT(indiceEtoileDown()));
    connect(suivant,SIGNAL(clicked()),this,SLOT(indiceEtoileUp()));
    connect(solarSize,SIGNAL(valueChanged(int)),toto2,SLOT(changeSize(int)));
    connect(solarSize,SIGNAL(valueChanged(int)),this,SLOT(modifTaille(int)));
    }



}

void MainWindow::window2()
{


        //delete masseEtoileLabel;
        //delete lcdMasseEtoile;
        //delete nbplanetesLabel;
        //delete lcdNbplanetes;
        delete valider2;
        delete precedent;
        delete suivant;
        delete solarSize;
        delete tailleSoleil;
        //delete selectionnerFond;
        //delete toto;
        //SDL_Quit();
        //delete Layout1;
    delete toto2;
    SDL_Quit();

    delete Layout2;


        paramettresplanetes = new QVector<QString>;

        title = new QString;
        *title="caractéristiques de la planète ";
        this->setWindowTitle(title->append(QString::number(1)));
        title->clear();

        QLabel *nomplanete = new QLabel(tr("nom de la planète"));
        QLabel *periodeplanete = new QLabel(tr("periode de la planète"));
        QLabel *phaseplanete = new QLabel(tr("phase de la planète"));
        QLabel *periodePropre = new QLabel(tr("période de rotation propre"));
        enterName = new QLineEdit;
        enterPriodeplanete = new QLineEdit;
        enterPhaseplanete = new QLineEdit;
        entrerPeriodePropre = new QLineEdit;


        Lancer = new QPushButton(tr("&lancer"));
        valider = new QPushButton(tr("valider planète"));
        Lancer->hide();
        grid = new QGridLayout;
        //quitter = new QPushButton(tr("quitter"));
        suivant = new QPushButton(tr("suivant"));
        precedent = new QPushButton(tr("precedent"));
        solarSize = new QSlider(Qt::Horizontal);
        solarSize->setValue(1);
        solarSize->setRange(1,6);
        planet = new planetSelection;

        grid->addWidget(nomplanete,0,0);
        grid->addWidget(periodeplanete,1,0);
        grid->addWidget(phaseplanete,2,0);
        grid->addWidget(periodePropre,3,0);
        grid->addWidget(enterName,0,1);
        grid->addWidget(enterPriodeplanete,1,1);
        grid->addWidget(enterPhaseplanete,2,1);
        grid->addWidget(entrerPeriodePropre,3,1);
        grid->addWidget(Lancer,6,0);
        grid->addWidget(valider,6,1);
        //grid->addWidget(Lancer);
       // grid->addWidget(quitter);
        grid->addWidget(planet,4,0,2,1);
        grid->addWidget(precedent,4,1,1,1);
        grid->addWidget(suivant,5,1,1,1);
        grid->addWidget(solarSize,6,0,1,1);

        setLayout(grid);
        connect(valider,SIGNAL(clicked()),this,SLOT(validerplanete()));
        //connect(quitter,SIGNAL(clicked()),qApp,SLOT(quit()));
        connect(suivant,SIGNAL(clicked()),planet,SLOT(goUp()));
        connect(precedent,SIGNAL(clicked()),planet,SLOT(goDown()));
        connect(suivant,SIGNAL(clicked()),this,SLOT(selectPlanetUp()));
        connect(precedent,SIGNAL(clicked()),this,SLOT(selectPlanetDown()));
        connect(solarSize,SIGNAL(valueChanged(int)),planet,SLOT(changeSize(int)));


        QDoubleValidator *validator1 = new QDoubleValidator(enterPhaseplanete);
        validator1->setNotation(QDoubleValidator::StandardNotation);
        validator1->setBottom(0.0);
        validator1->setDecimals(0);
        validator1->setTop(6.28);

        /*QDoubleValidator *validator2 = new QDoubleValidator(enterExentriciteElipse);
        validator2->setNotation(QDoubleValidator::StandardNotation);
        validator2->setBottom(0.0);
        validator2->setDecimals(1);
        validator2->setTop(0.9);*/

        QDoubleValidator *validator3 = new QDoubleValidator(entrerPeriodePropre);
        validator3->setNotation(QDoubleValidator::StandardNotation);
        validator3->setBottom(1.);
        validator3->setDecimals(0);
        validator3->setTop(9.0);

        QDoubleValidator *validator4 = new QDoubleValidator(enterPriodeplanete);
        validator4->setNotation(QDoubleValidator::StandardNotation);
        validator4->setBottom(1.);
        validator4->setDecimals(0);
        validator4->setTop(20.0);

        enterPhaseplanete->setValidator(validator1);
        entrerPeriodePropre->setValidator(validator3);
        enterPriodeplanete->setValidator(validator4);

}

void MainWindow::validerplanete(){


    if(enterName->text().isEmpty() || enterPriodeplanete->text().isEmpty() || enterPhaseplanete->text().isEmpty() || entrerPeriodePropre->text().isEmpty() ){
        QMessageBox msg;
        msg.setText(tr("Entrez tous les paramèttes"));
        msg.exec();
    }else if(numeroplanete+1 >= nbplanetes->value()){

        int validator = 0;
        if(numeroplanete >= 1)
            {
                for ( int ii = 1; ii <= (numeroplanete-1)*4 + 1 ; ii+=4 ){
            if(enterPriodeplanete->text() == paramettresplanetes->at(ii) )
            {
                QMessageBox msg;
                msg.setText(tr("les planettes ne doivent pas avoir une periode commune"));
                msg.exec();
                enterPriodeplanete->clear();
                validator = 1;


            }
        }
                }
        if (validator == 0)
{

        QMessageBox msg;
        msg.setText(tr("planète enregistrée"));
        msg.exec();
        paramettresplanetes->push_back(enterName->text());
        paramettresplanetes->push_back(enterPriodeplanete->text());
        paramettresplanetes->push_back(enterPhaseplanete->text());
        paramettresplanetes->push_back(entrerPeriodePropre->text());
        planet_sizes.push_back( solarSize->value());

        if (texture_id >3 || texture_id < 0){
                 texture_id= 0;
            }
        textures_vector_id.push_back(texture_id);
        if (taille_soleil > 8 || taille_soleil < 1)
            taille_soleil = 1;

        enterName->clear();
        enterPriodeplanete->clear();
        enterPhaseplanete->clear();
        entrerPeriodePropre->clear();
        enterName->setEnabled(false);
        enterPriodeplanete->setEnabled(false);
        enterPhaseplanete->setEnabled(false);
        entrerPeriodePropre->setEnabled(false);
        connect(Lancer,SIGNAL(clicked()),this,SLOT(lancerCalculs()));
        //connect(quitter,SIGNAL(clicked()),qApp,SLOT(quit()));
        valider->hide();
        planet->hide();
        precedent->hide();
        suivant->hide();
        solarSize->hide();
        Lancer->show();
}
    }



    else{
        int validator = 0;
        if(numeroplanete >= 1)
            {
                for ( int ii = 1; ii <= (numeroplanete-1)*4 + 1 ; ii+=4 ){
            if(enterPriodeplanete->text() == paramettresplanetes->at(ii) )
            {
                QMessageBox msg;
                msg.setText(tr("les planettes ne doivent pas avoir une periode commune"));
                msg.exec();
                enterPriodeplanete->clear();
                validator = 1;


            }
        }
                }
        if (validator == 0)
{
            QMessageBox msg;
            msg.setText(tr("planète enregistrée"));
            msg.exec();
          paramettresplanetes->push_back(enterName->text());
          paramettresplanetes->push_back(enterPriodeplanete->text());
          paramettresplanetes->push_back(enterPhaseplanete->text());
          paramettresplanetes->push_back(entrerPeriodePropre->text());
          enterName->clear();
          enterPriodeplanete->clear();
          enterPhaseplanete->clear();
          entrerPeriodePropre->clear();
          if (texture_id >3 || texture_id < 0){
                   texture_id= 0;
              }
          textures_vector_id.push_back(texture_id);

          planet_sizes.push_back(solarSize->value());
          numeroplanete++;
          int num2str=numeroplanete+1;
          title->clear();
          *title = "caractéristiques de la planète ";
          this->setWindowTitle(title->append(QString::number(num2str)));
          Lancer->hide();
        }
     }
}

void MainWindow::lancerCalculs(){
    Lancer->hide();


    CalculsAlignement calculs(*paramettresplanetes,nbplanetes->value(),masseEtoile->value(),it,it2,taille_soleil,planet_sizes,textures_vector_id);
    calculs.lancer();

}

void MainWindow::indiceFond(){
    it++;

    if (it >4 || it < 0){
 it = 0;
    }
}

void MainWindow::indiceEtoileUp(){
    it2++;
    if (it2 >3 || it2 < 0){
 it2 = 0;
    }
}

void MainWindow::indiceEtoileDown(){
    it2--;
    if (it2 >3 || it2 < 0){
 it2 = 3;
    }
}

void MainWindow::modifTaille(int size){
    taille_soleil = size;

}

void MainWindow::selectPlanetUp(){
    texture_id++;
if (texture_id >3 || texture_id < 0){
         texture_id= 0;
    }
}

void MainWindow::selectPlanetDown(){
    texture_id--;
if (texture_id >3 || texture_id < 0){
         texture_id = 3;
    }
}
