#ifndef PLANETSELECTION_H
#define PLANETSELECTION_H

#include <QGLWidget>

#include"vector"
#include "sdlglutils.h"

class planetSelection : public QGLWidget
{
    Q_OBJECT
public:
    explicit planetSelection(QWidget *parent = 0);
    ~planetSelection();

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

#endif // PLANETSELECTION_H
