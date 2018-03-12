#ifndef CALCULSALIGNEMENT_H
#define CALCULSALIGNEMENT_H


#include<QVector>
#include<QString>
#include<string>
#include<vector>
#include "sdlglutils.h"
#include"mainwindow.h"

class CalculsAlignement{
public:
    CalculsAlignement();
    CalculsAlignement(QVector<QString>, int, int, int, int, int, std::vector<int> planet_vector, std::vector<int> idplanetestextures);
    void lancer();
private:
   //int nb_planetes;
   std::vector<double> Periodes_;
   std::vector<double> Phases_;
   std::vector<double> PeriodesPropres;
   //std::string Names_;
   QString periode;
   QString phase;
   QString exentricitee;
   QString name;
   QString periodespropres;
public:
   int nb_planetes;
   int masse_etoile;
   double *x,*y,rayons, *angle2;
    std::vector<GLuint> textures;
    std::vector<int> planetes_sizes;
    std::vector<int> idplanetes;
    GLuint textureFond_;
    int idciel;
    int idetoile;
    int solar_size;
};

#endif // CALCULSALIGNEMENT_H
