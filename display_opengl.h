#ifndef DISPLAY_OPENGL_H
#define DISPLAY_OPENGL_H

#include"vector"
#include "sdlglutils.h"



void afficher(int, double[], double[], std::vector<GLuint> textures, double angle[], int taille_soleil, std::vector<int> planetes_sizes);
void Sphere(int,int);
void Dessiner(int, double[], double[], std::vector<GLuint> textures, double angle[],int taille_soleil,std::vector<int> planetes);
void loadCubemap(std::vector<GLuint> textures);
std::vector<GLuint> chargerTextures(int id_etoile, int id_ciel, std::vector<int> id_planetes);

#endif // DISPLAY_OPENGL_H
