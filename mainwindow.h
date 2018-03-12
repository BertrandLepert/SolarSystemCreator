#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QVBoxLayout>
#include<QLineEdit>
#include<QTextEdit>
#include<QPushButton>
#include<QMap>
#include<QString>
#include<QSlider>
#include<QLabel>
#include<QLCDNumber>
#include<QMap>
#include "sdlglutils.h"
#include<vector>
#include<QGLWidget>
#include"gl_widget.h"
#include"salorselectionglwidget.h"
#include"planetselection.h"
#define  pi 3.14159




class MainWindow: public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
public slots:
    void window1();
    void window2();
    void solarSelection();
    void validerplanete();
    void lancerCalculs();
    void indiceFond();
    void indiceEtoileUp();
    void indiceEtoileDown();
    void modifTaille(int size);
    void selectPlanetUp();
    void selectPlanetDown();
public:
    QSlider *nbplanetes;
    QSlider *masseEtoile;
    QSlider *solarSize;
    QPushButton *enterProgram;
    QPushButton *valider;
    QPushButton *valider2;
    QPushButton *Lancer;
    QPushButton *quitter;
    QPushButton *selectionnerFond;
    QPushButton *precedent;
    QPushButton *suivant;
    QLabel *masseEtoileLabel;
    QLabel *nbplanetesLabel;
    QLabel *tailleSoleil;
    QVBoxLayout *Layout1;
    QGridLayout *Layout2;
    QGridLayout *grid;
    QLCDNumber *lcdMasseEtoile;
    QLCDNumber *lcdNbplanetes;
    QLineEdit *enterName;
    QLineEdit *enterPriodeplanete;
    QLineEdit *enterPhaseplanete;
    QLineEdit *entrerPeriodePropre;
    QVector<QString> *paramettresplanetes;
    QString *title;
    GLuint ciel;
    int numeroplanete;
    int it;
    int it2;
    int texture_id;
    int taille_soleil;
    MyGLWidget *toto;
    SolarSelectionGLWidget *toto2;
    planetSelection *planet;
    std::vector<int> textures_vector_id;
    std::vector<int> planet_sizes;

public:
    //void initializeGL();
    //void resizeGL(int width, int height);
};

#endif // MAINWINDOW_H
