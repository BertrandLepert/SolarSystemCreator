#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include<display_opengl.h>


class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();
signals:

public slots:

    void refresh();
private:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    QSize minimumSizeHint() const;


private:

    int textureId1;
    std::vector<GLuint> textures;
    //
};

#endif // MYGLWIDGET_H
