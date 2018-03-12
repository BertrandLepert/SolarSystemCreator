#include "salorselectionglwidget.h"

#include <QtWidgets>
#include <QtOpenGL>
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



SolarSelectionGLWidget::SolarSelectionGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    angle = 0.5;
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);


}

SolarSelectionGLWidget::~SolarSelectionGLWidget()
{
}

QSize SolarSelectionGLWidget::minimumSizeHint() const
{
    return QSize(70, 70);
}




void SolarSelectionGLWidget::initializeGL()
{
    glShadeModel(GL_SMOOTH);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


        GLuint id1 = loadTexture("sun.bmp",false);

               textures.push_back(id1);
        GLuint id2 = loadTexture("sunmap.jpg",false);
                textures.push_back(id2);

        GLuint id3 = loadTexture("Acheron.jpg",false);
                     textures.push_back(id3);

                     GLuint id4 = loadTexture("460886161.jpg",false);
                              textures.push_back(id4);


        if(textureId>3 || textureId<0 )
            textureId = 0;



        glLoadIdentity();
   // static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
    //glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void SolarSelectionGLWidget::paintGL()
{
    if (size_<=0 || size_>8)
    {
        size_=1;
    }


    glPushMatrix();

    //glTranslatef(0.0, 0.0, -10.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,textures.at(textureId));
    glRotated(angle,0,1,0);
    GLUquadric* soleil = gluNewQuadric();

    gluQuadricTexture(soleil,GL_TRUE);

   gluSphere(soleil,0.12*size_,20,20);

glDisable(GL_TEXTURE_2D);
glPopMatrix();

angle = angle + 1;


}

void SolarSelectionGLWidget::changeSize(int size)
{
 size_ = size;
}

void SolarSelectionGLWidget::goUp(){
    textureId++;

    if (textureId >3 || textureId < 0){
 textureId = 0;
    }
}

void SolarSelectionGLWidget::goDown(){
    textureId--;

    if (textureId >3 || textureId < 0){
 textureId = 3;
    }
}

void SolarSelectionGLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
  glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    glMatrixMode(GL_MODELVIEW);
}
