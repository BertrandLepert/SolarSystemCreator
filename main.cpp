#include <QtOpenGL>
#include "mainwindow.h"
#include <QApplication>
#include<QRect>
#include "sdlglutils.h"
#include"sdlglutils.cpp"
using namespace std;

int main(int argc, char *argv[])
{



    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    w.setFixedSize(400,600);

    QDesktopWidget bureau;
    QRect surface_bureau = bureau.screenGeometry();
    int x = surface_bureau.width()/2 - w.width()/2;
    int y = surface_bureau.height()/2 - w.height()/2;

   w.move(QPoint(x, y));


    return app.exec();
}
