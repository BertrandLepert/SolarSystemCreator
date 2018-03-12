#ifndef SALORSELECTIONGLWIDGET_H
#define SALORSELECTIONGLWIDGET_H

#include <QGLWidget>

#include"vector"
#include "sdlglutils.h"

class SolarSelectionGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit SolarSelectionGLWidget(QWidget *parent = 0);
    ~SolarSelectionGLWidget();

public slots:

    void goUp();
    void goDown();
    void changeSize(int size);
private:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    QSize minimumSizeHint() const;


private:

    int textureId;
    std::vector<GLuint> textures;
    int angle;
    int size_;
    //
};

#endif // SALORSELECTIONGLWIDGET_H
