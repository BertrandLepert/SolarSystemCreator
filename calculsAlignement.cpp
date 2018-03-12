#include "calculsAlignement.h"
#include <cmath>
#include <iostream>
#include<stdio.h>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include<QString>
#include<QVector>
#include<QStringList>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<display_opengl.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include<math.h>
#include "sdlglutils.h"

#include<GL/glut.h>


CalculsAlignement::CalculsAlignement(QVector<QString> paramettresplanetes, int nbplanetes, int masseEtoile, int it, int it2, int taille_soleil, std::vector<int> planet_vector, std::vector<int> idplanetestextures)
{
    idciel = it;
    idetoile = it2;
    solar_size = taille_soleil;
    planetes_sizes = planet_vector;
    idplanetes = idplanetestextures;

    masse_etoile = masseEtoile;
    nb_planetes = nbplanetes;
    int ii = 0;
    //QVector<QString>::iterator i;
    for ( int i = 0; i != nb_planetes;i++){
     name = paramettresplanetes.value(ii);//.split("");
     //Names_( QString(name[i]).to );
    ii++;
     periode= paramettresplanetes.value(ii);//.split("");
     Periodes_.push_back(QString(periode).toDouble());
    ii++;
     phase = paramettresplanetes.value(ii);//.split("");
     Phases_.push_back(QString(phase).toDouble());
    ii++;
    periodespropres = paramettresplanetes.value(ii);
    PeriodesPropres.push_back(QString(periodespropres).toDouble());
    ii++;
    }
}

void CalculsAlignement::lancer(){

    double PI = 3.14;
    double pi_carre = pow(PI,2);
        ////variables:

        //double UA = 149597870700/*unité astronomique*/
        double constante_grav =1.33* pow(10.,20.);// * pow(10.,20.); //6.67384 * pow( 10., -11. )*1.989 * pow(10,30);/*en m^3.Kg^-1.s-1*/

        //paramètres du système solaire.
        /*cout << "entrez le nombre de planetes" << endl; //nombre de planetes à entrer dans la console.
                cin >> nb_planetes;
        cout << "entrez la masse de l'étoile" << endl; //masse de l'étoile du système concerné.
        cin >> masse_etoile;*/
        //masse_etoile =;



        double temps = 0.;
        double a;
        double a_div;
        double max_div;
        for(int i=0; i < nb_planetes ; i++){
         // initialisation de la variable temps
            a=(Periodes_.at(i)* constante_grav*(masse_etoile*1.)*pow(10,6))/(4*pi_carre );
        if(a<0)
            a_div =a*(-1);
        else
            a_div=a;
        if(max_div<a_div)
            max_div = a_div;
        }


        SDL_Init(SDL_INIT_VIDEO);
       // atexit(SDL_Quit);
        SDL_WM_SetCaption("SDL GL Application", NULL);
        const SDL_VideoInfo *videoInfo;

        videoInfo=SDL_GetVideoInfo();

        SDL_SetVideoMode( videoInfo->current_w,videoInfo->current_h, 32, SDL_NOFRAME | SDL_OPENGL );
        SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_HWSURFACE);

        SDL_Event event;
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        gluPerspective(70,(double)640/480,1,1000);
        glEnable(GL_DEPTH_TEST);


        //GLuint identifiant_texture = loadTexture("4.jpg");
             textures = chargerTextures(idetoile,idciel,idplanetes);

        for (;;) { //boucle de calcul du rayons (coordonnés polaires), des positions (coordonnées cartésiennes) et du déterminant.

            SDL_PollEvent(&event);
            switch(event.type)
            {
                case SDL_QUIT:
                    SDL_Quit();
            }



            angle2 = new double [nb_planetes];
            x = new double[nb_planetes];
                y = new double[nb_planetes];

            for (int i = 0; i < nb_planetes; i++) {


                a=(Periodes_.at(i) * constante_grav*(masse_etoile*1.)*pow(10,6))/(4*pi_carre );
                rayons = (a/max_div)*(1-pow(/*Exentricites_.at(i)*/ 0.,2))/ (1. + /*Exentricites_.at(i)*/ 0. * cos(2. * PI/ Periodes_.at(i) *temps + Phases_.at(i))); //rayon des l'éllipses à l'instant t

                x[i]=(rayons +  0.035 * solar_size)* cos(2. * PI/ Periodes_.at(i) * temps + Phases_.at(i)); // positions des plannettes sur l'axe x à l'instant t.
                y[i]=(rayons +  0.035 * solar_size) *sin(2. * PI/ Periodes_.at(i) * temps  + Phases_.at(i)); // positions des planetes sur l'axe y à l'instant t.

                angle2[i] = 2. * PI  /PeriodesPropres.at(i) * temps *360. ;


            }


            afficher(nb_planetes,x,y,textures,angle2,solar_size,planetes_sizes);


            temps += 1 / (365.25); //incrémentation du temps


        }


}
