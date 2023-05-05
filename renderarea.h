#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include<QPainter>

class RenderArea : public QWidget
{
    Q_OBJECT
public:

    explicit RenderArea(QWidget *parent = nullptr);
    QSize minimumSizeHint() const  override;
    QSize sizeHint() const override;

signals:
    void changeStatus(QString);
    void addVertexPos(QPoint) ;
    void addPointPos(QPoint);
    void deletAllPoint();
    void triagleActivate();

public slots:
    void trianglepress();
    void fullVertex();
    void drowLineWithPoint(QPoint,QPoint);
    void clearArena();
    void paintPoint();


protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent (QResizeEvent *event) override;

private:
    void drawBorder();
    void drawPoint(QPoint pos);
    void drawLine(QPoint pos1,QPoint pos2);
    void resizeImage( const QSize &newSize);
    void statusTrianglePs();
    QImage image;
    bool trianglepresset = false,paintVertex = true;




};

#endif // RENDERAREA_H
