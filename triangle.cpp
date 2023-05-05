#include "triangle.h"
#include "qdebug.h"
#include <iostream>
#include <QFile>

Triangle::Triangle(QObject *parent)
    : QObject{parent}
{
    asd  = new QFile("asd.csv");
    asd->open(QIODevice::WriteOnly | QIODevice::Text);
}

void Triangle::addVertex(QPoint point)
{
    switch(vec.length())
    {
    case 1:
        vec.append(point);
        emit drawLinePos(vec[0],vec[1]);
        break;
    case 2:
        vec.append(point);
        emit drawLinePos(vec[0],vec[2]);
        emit drawLinePos(vec[2],vec[1]);
        emit vecOverflow() ;
        break;
    default:
        vec.append(point);
        break;
    }
}

int Triangle::farPointI()
{
    for(int i = 0;i < vec.length(); i++)
    {
        disToPoint[i] = distace(vec[i],*pointPos);
    }
    float *max = &disToPoint[0];
    max = std::max_element(disToPoint,disToPoint+3);
    return max-disToPoint;
}

float Triangle::distace(QPoint point1,QPoint point2)
{
    return sqrt (float(pow(abs(point1.y() - point2.y()),2) +
                 pow(abs(point1.x() - point2.x()),2)));
}

void Triangle::findKB(QPoint point1,QPoint point2,int i)
{
    k[i] = findk(point1,point2);
    b[i] = (point1.y() - k[i]*point1.x());
}

float Triangle::findk(QPoint point1,QPoint point2)
{
    return float(point1.y()-point2.y())/float(point1.x() - point2.x());
}

void Triangle::statusBarUpdate(QString str)
{
    emit statusBarMessige(str);
}

//__________________________
//slots
//__________________________

void Triangle::deleteAllVertex()
{
    vec.clear();
}

void Triangle::addPoint(QPoint point)
{
    pointPos = new QPoint(point);
    int maxDisI =farPointI();
    QPoint farPoint = vec[maxDisI];
    float triagleK[2];
    emit drawLinePos(farPoint,*pointPos);
    findKB(farPoint,*pointPos,0);
    vec.removeAt(maxDisI);

    for(int i = 0;i < 2;i++)
        triagleK[i]=atan(findk(farPoint,vec[i]));

    std::stable_sort(triagleK,triagleK+2);

    findKB(vec[0],vec[1],1);
    vec.insert(maxDisI,farPoint);

    QPoint crossPoint ((b[1]-b[0])/(k[0]-k[1]),k[0]*(b[1]-b[0])/(k[0]-k[1])+b[0]);
    //QTextStream out(asd);
    if(distace(crossPoint,farPoint) > distace(*pointPos,farPoint) && ((triagleK[0]) < atan(k[0])) && (atan(k[0])< (triagleK[1])))
        statusBarUpdate("into");
    else
        statusBarUpdate("out");

}
