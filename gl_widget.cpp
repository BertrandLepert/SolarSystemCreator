// myglwidget.cpp

#include <QtWidgets>
#include <QtOpenGL>

#include "gl_widget.h"


MyGLWidget::MyGLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);


}

MyGLWidget::~MyGLWidget()
{
}

QSize MyGLWidget::minimumSizeHint() const
{
    return QSize(170, 170);
}




void MyGLWidget::initializeGL()
{
    glShadeModel(GL_SMOOTH);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


        GLuint id1 = loadTexture("orion_1080p.jpg",false);

               textures.push_back(id1);
        GLuint id2 = loadTexture("4.jpg",false);
                textures.push_back(id2);

        GLuint id3 = loadTexture("5.jpg",false);
                     textures.push_back(id3);

                     GLuint id4 = loadTexture("6.jpg",false);
                              textures.push_back(id4);
                              GLuint id5 = loadTexture("7.png",false);
                                       textures.push_back(id5);

        if(textureId1>4 || textureId1<0 )
            textureId1 = 0;



        glLoadIdentity();
   // static GLfloat lightPosition[4] = { 0, 0, 10, 1.0 };
    //glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void MyGLWidget::paintGL()
{





    //glTranslatef(0.0, 0.0, -10.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D,textures.at(textureId1));


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

void MyGLWidget::refresh(){
    textureId1++;

    if (textureId1>4 || textureId1 < 0){
 textureId1 = 0;
    }
}

void MyGLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
  glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    glMatrixMode(GL_MODELVIEW);
}
