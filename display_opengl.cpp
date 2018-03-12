#include <display_opengl.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include<math.h>
#include "sdlglutils.h"
#include"vector"
#include <SOIL/SOIL.h>
#include<string>
#include"SDL/SDL_ttf.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>

using namespace std;



void afficher(int Nb, double x[] , double y[], std::vector<GLuint> textures, double angle[], int taille_soleil, std::vector<int> planetes_sizes){
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    gluLookAt(20,0,0,0,0,0,0,0,1.5);
    glScalef(75,100,75);
        loadCubemap(textures);



    Uint32 last_time = SDL_GetTicks();
    Uint32 current_time,ellapsed_time;
    Uint32 start_time;

    //Dessiner();

    //for (;;)
    //{
       start_time = SDL_GetTicks();
       current_time = SDL_GetTicks();
       ellapsed_time = current_time - last_time;
       last_time = current_time;

       //angleZ += 0.05 * ellapsed_time;
       //angleX += 0.05 * ellapsed_time;
       Dessiner( Nb, x , y, textures, angle, taille_soleil,planetes_sizes);
       ellapsed_time = SDL_GetTicks() - start_time;
       if(ellapsed_time < 10)
       {
          SDL_Delay(10-ellapsed_time);
       }


}

void Sphere(int a,int b) {
float da = ( M_PI / a );
float db = ( 2.0f * M_PI / b );
glBegin(GL_QUADS);

glNormal3f(0,0,1);
for( int i = 0; i < a + 1 ; i++ ) {
 float r0 = sin ( i * da );
 float y0 = cos ( i * da );
 float r1 = sin ( (i+1) * da );
 float y1 = cos ( (i+1) * da );

 for( int j = 0; j < b + 1 ; j++ ) {
  float x0 = r0 * sin( j * db );
  float z0 = r0 * cos( j * db );
  float x1 = r0 * sin( (j+1) * db );
  float z1 = r0 * cos( (j+1) * db );

  float x2 = r1 * sin( j * db );
  float z2 = r1 * cos( j * db );
  float x3 = r1 * sin( (j+1) * db );
  float z3 = r1 * cos( (j+1) * db );

  //glColor3f((x0+x1+x2+x3)/4.0,(y0+y1)/2.0,(z0+z1+z2+z3)/4.0);

  glVertex3f(x0,y0,z0);
  glVertex3f(x1,y0,z1);
  glVertex3f(x3,y1,z3);
  glVertex3f(x2,y1,z2);
 }
}
glEnd();
}

void Dessiner(int Nb , double x[] , double y[], std::vector<GLuint> textures, double angle[], int taille_soleil, std::vector<int> planete_sizes)
{

    float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
        float mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};

        float mat_specular[] = {1.0f, 1.0f, 1.0f, 0.0001f};
        glScalef(0.015,0.0085,0.015);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0f);
        glLighti(GL_LIGHT0,GL_SPOT_EXPONENT,180.f);

        //glPushMatrix();

    glPushMatrix();
    GLUquadric* soleil = gluNewQuadric();
    glEnable(GL_TEXTURE_2D);
    gluQuadricTexture(soleil,GL_TRUE);
    glBindTexture(GL_TEXTURE_2D,textures.at(1));
    gluSphere(soleil,0.35 * taille_soleil,40,40);


    GLUquadric* planettes = gluNewQuadric();

    gluQuadricTexture(planettes,GL_TRUE);


    glPushMatrix();

            glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, no_mat);
            glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
            glMaterialf(GL_FRONT, GL_SHININESS, 0.01);
            glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
            float lt_direct[] = { 0, 0, 0, 0.0001 };

glEnable(GL_LIGHTING);


     /* Dessin 3D */
    for(int i = 0 ; i< Nb ; i++){
        glEnable(GL_LIGHT0);
        glLightfv( GL_LIGHT0, GL_POSITION, lt_direct );
        glPushMatrix();
        glTranslated(12*x[i],12*y[i],0);
        //glRotated(15,0,0,1);
        glRotated(angle[i],0,0,1);
        glBindTexture(GL_TEXTURE_2D,textures.at(i+2));
        gluSphere(planettes,0.12*planete_sizes.at(i),20,20);
        glDisable(GL_LIGHT0);

    glPopMatrix();

}
    glPopMatrix();
gluDeleteQuadric(soleil);
gluDeleteQuadric(planettes);
glFlush();
SDL_GL_SwapBuffers();
glDisable(GL_TEXTURE_2D);

glDisable(GL_LIGHTING);
}


void loadCubemap(std::vector<GLuint> textures)
{



    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,textures.at(0));


   glBegin(GL_QUADS);
       glTexCoord2d(0,1);  glVertex3d(1,1,1);
       glTexCoord2d(0,0);  glVertex3d(1,1,-1);
       glTexCoord2d(1,0);  glVertex3d(-1,1,-1);
       glTexCoord2d(1,1);  glVertex3d(-1,1,1);
       glEnd();

       glBegin(GL_QUADS);
      glTexCoord2d(0,1); glVertex3d(1,-1,1);
      glTexCoord2d(0,0); glVertex3d(1,-1,-1);
      glTexCoord2d(1,0); glVertex3d(1,1,-1);
      glTexCoord2d(1,1); glVertex3d(1,1,1);
       glEnd();


glBegin(GL_QUADS);
      glTexCoord2d(0,1); glVertex3d(-1,-1,1);
       glTexCoord2d(0,0); glVertex3d(-1,-1,-1);
       glTexCoord2d(1,0); glVertex3d(1,-1,-1);
       glTexCoord2d(1,1); glVertex3d(1,-1,1);
       glEnd();

glBegin(GL_QUADS);
         glTexCoord2d(0,1);  glVertex3d(-1,1,1);
        glTexCoord2d(0,0);   glVertex3d(-1,1,-1);
          glTexCoord2d(1,0); glVertex3d(-1,-1,-1);
         glTexCoord2d(1,1);  glVertex3d(-1,-1,1);
           glEnd();

glBegin(GL_QUADS);

 glTexCoord2d(0,1);   glVertex3d(1,1,-1);
  glTexCoord2d(0,0); glVertex3d(1,-1,-1);
  glTexCoord2d(1,0);  glVertex3d(-1,-1,-1);
   glTexCoord2d(1,1); glVertex3d(-1,1,-1);

glEnd();
glDisable(GL_TEXTURE_2D);


}


std::vector<GLuint> chargerTextures(int id_etoile, int id_ciel, std::vector<int> id_planetes)
{
    GLuint id1;
    std::vector<GLuint> TexturesVector;
 int ciel = id_ciel;
 int etoile = id_etoile;
std::vector<int> planetes = id_planetes;
    switch(ciel){
    case  0:
        id1 = loadTexture("orion_1080p.jpg",false);
        TexturesVector.push_back(id1);
        break;
    case 1:
         id1 = loadTexture("4.jpg",false);
        TexturesVector.push_back(id1);
        break;
    case  2:
        id1 = loadTexture("5.jpg",false);
        TexturesVector.push_back(id1);
        break;
    case  3:
        id1 = loadTexture("6.jpg",false);
        TexturesVector.push_back(id1);
        break;
    case  4:
       id1 = loadTexture("7.png",false);
             TexturesVector.push_back(id1);
             break;
    default:
        id1 = loadTexture("orion_1080p.jpg",false);
        TexturesVector.push_back(id1);
        break;

    }

    switch(etoile){
    case  0:
         id1 = loadTexture("sun.bmp",false);
        TexturesVector.push_back(id1);
        break;
    case  1:
        id1 = loadTexture("sunmap.jpg",false);
                TexturesVector.push_back(id1);
                break;
    case  2:
        id1 = loadTexture("Acheron.jpg",false);
        TexturesVector.push_back(id1);
        break;
    case  3:
        id1 = loadTexture("460886161.jpg",false);
        TexturesVector.push_back(id1);
         break;
default:
        id1 = loadTexture("sun.bmp",false);
       TexturesVector.push_back(id1);
       break;
    }
GLuint identifiant_texture2;
   for( int i =0 ; i < id_planetes.size() ; i++)
{

        switch(planetes.at(i)){
case 0:
     identifiant_texture2 = loadTexture("earthmap1k.jpg",false);
    TexturesVector.push_back(identifiant_texture2);
    break;
case 1:
    identifiant_texture2 =   loadTexture("Jupiter_s.jpg",false);
    TexturesVector.push_back(identifiant_texture2);
    break;
case 2:
    identifiant_texture2 = loadTexture("sand.jpg",false);
    TexturesVector.push_back(identifiant_texture2);
    break;
case 3:
    identifiant_texture2 = loadTexture("stone_1.jpg",false);
    TexturesVector.push_back(identifiant_texture2);
    break;
}
        }


return TexturesVector;
}

