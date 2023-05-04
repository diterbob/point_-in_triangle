#include "window.h"




window::window()
{
    renderarea  = new RenderArea;
    triangle = new Triangle;

    buttonTriangl =new QPushButton(tr("&Triangl"),this);
    buttonPoint =new QPushButton(tr("&Point"),this);
    buttonClear =new QPushButton(tr("&Clear"),this);
    statusbar = new QStatusBar(this);
    triangleEn();
    statusbar->setSizeGripEnabled(0);
    statusbar->setFixedHeight(15);

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(2, 1);
    mainLayout->setColumnStretch(4, 1);
    mainLayout->setColumnStretch(6, 1);
    mainLayout->addWidget(renderarea, 0, 0, 1, 7);
    mainLayout->addWidget(buttonTriangl,1,1);
    mainLayout->addWidget(buttonPoint,1,3);
    mainLayout->addWidget(buttonClear,1,5);
    mainLayout->addWidget(statusbar,2,0,1,7);

    setLayout(mainLayout);

    connect(buttonTriangl,&QAbstractButton::clicked,renderarea,&RenderArea::trianglepress);
    connect(buttonClear,&QAbstractButton::clicked,renderarea,&RenderArea::clearArena);
    connect(buttonPoint,&QAbstractButton::clicked,renderarea,&RenderArea::paintPoint);
    connect(renderarea,&RenderArea::deletAllPoint,triangle,&Triangle::deleteAllVertex);
    connect(renderarea,SIGNAL(triagleActivate()),this,SLOT(triangleEn()));
    connect(renderarea,SIGNAL(addPointPos(QPoint)),triangle,SLOT(addPoint(QPoint)));
    connect(renderarea,SIGNAL(addVertexPos(QPoint)),triangle,SLOT(addVertex(QPoint)));
    connect(triangle,SIGNAL(vecOverflow()),this,SLOT(triangleDis()));
    connect(triangle,SIGNAL(vecOverflow()),renderarea,SLOT(fullVertex()));
    connect(renderarea,SIGNAL(changeStatus(QString)),statusbar,SLOT(showMessage(QString)));
    connect(triangle,SIGNAL(drawLinePos(QPoint,QPoint)),renderarea,SLOT(drowLineWithPoint(QPoint,QPoint)));

}

void window::triangleDis()
{
   buttonTriangl->setEnabled(false);
   buttonClear->setEnabled(true);
   buttonPoint->setEnabled(true);
   statusbar->showMessage(tr("add point or clear"));;
}

void window::triangleEn()
{
   buttonTriangl->setEnabled(true);
   buttonClear->setEnabled(false);
   buttonPoint->setEnabled(false);
   statusbar->showMessage(tr("Reday to work"));
}
