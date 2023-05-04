#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QtWidgets>

#include "renderarea.h"
#include "triangle.h"

class RenderArea;

class window : public QWidget
{
    Q_OBJECT
public:
    window();

signals:

public slots:
    void triangleEn();
    void triangleDis();

private:
    RenderArea *renderarea;
    Triangle *triangle;
    QStatusBar *statusbar ;
    QPushButton *buttonTriangl,*buttonPoint,*buttonClear;
};

#endif // WINDOW_H
