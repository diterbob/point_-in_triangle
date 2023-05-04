#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QObject>
#include <QPoint>
#include <QFile>

class Triangle : public QObject
{
    Q_OBJECT
public:
    explicit Triangle(QObject *parent = nullptr);

signals:
    void vecOverflow();
    void drawLinePos(QPoint,QPoint);
    void poinInBorder(bool);

public slots:
    void addVertex(QPoint point);
    void addPoint(QPoint point);
    void deleteAllVertex();

protected:

private:
    QList<QPoint> vec;
    QPoint *pointPos;

    QFile *asd ;

    void findKB(QPoint point1,QPoint point2,int i);
    float findk(QPoint point1,QPoint point2);
    float distace(QPoint point1,QPoint point2);
    int farPointI();
    float disToPoint [3],k[2],b[2];


};

#endif // TRIANGLE_H
